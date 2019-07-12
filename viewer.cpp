#
/*
 *    Copyright (C) 2014 - 2018
 *    Jan van Katwijk (J.vanKatwijk@gmail.com)
 *    Lazy Chair Programming
 *
 *    This file is part of the SDR-J
 *    Many of the ideas as implemented in SDR-J are derived from
 *    other work, made available through the GNU general Public License. 
 *    All copyrights of the original authors are recognized.
 *
 *    SDR-J is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    SDR-J is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with SDR-J; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#include	<QSettings>
#include	<QMessageBox>
#include	<QFileDialog>
#include	<QDebug>
#include	<QDateTime>
#include	"viewer.h"
#include	"popup-keypad.h"
#include	"device-handler.h"
#ifdef	HAVE_SDRPLAY
#include	"sdrplay-handler.h"
#endif
#ifdef	HAVE_AIRSPY
#include	"airspy-handler.h"
#endif
#ifdef	HAVE_RTLSDR
#include	"rtlsdr-handler.h"
#endif
#ifdef	HAVE_HACKRF
#include	"hackrf-handler.h"
#endif
#ifdef	HAVE_LIME
#include	"lime-handler.h"
#endif
#include	"spectrum-scope.h"
#include	"waterfall-scope.h"
#ifdef __MINGW32__
#include	<iostream>
#endif
#

#define	KHz(x)		(x * 1000)
#define	MHz(x)		(KHz (x) * 1000)
#define	FFT_SIZE	(16 * 32768)

static
float Window [FFT_SIZE];
/*
 *	We use the creation function merely to set up the
 *	user interface and make the connections between the
 *	gui elements and the handling agents. All real action
 *	is embedded in actions, initiated by gui buttons
 */
	Viewer::Viewer (QSettings	*Si,
	                QWidget		*parent): QDialog (parent) {
int k;
// 	the setup for the generated part of the ui
	setupUi (this);
	spectrumSettings		= Si;
	this	-> rasterSize		= 50;
	this	-> displaySize =
	             spectrumSettings -> value ("displaySize", 1024). toInt ();
	if ((displaySize & (displaySize - 1)) != 0)
	   displaySize	= 1024;

	HF_Scope_1	= new spectrumScope (hf_spectrumscope,
	                                           displaySize);
	connect (HF_Scope_1, SIGNAL (leftClicked (int)),
	         this, SLOT (adjustFrequency (int)));
	HF_Scope_2	= new waterfallScope (hf_waterfallscope,
	                                      displaySize, rasterSize);
	connect (HF_Scope_2, SIGNAL (leftClicked (int)),
	         this, SLOT (adjustFrequency (int)));
	try {
	   theDevice	= setDevice ();
	} catch (int e) {
	   fprintf (stderr, "no device found\n");
	   delete HF_Scope_1;
	   exit (21);
	}
	connect (theDevice, SIGNAL (handleSamples (void)),
	         this, SLOT (handleSamples (void)));

	theDevice	-> setVFOFrequency (theDevice -> defaultFrequency ());
	HF_Scope_1	-> setBitDepth (theDevice -> bitDepth ());

	mykeyPad	= new keyPad (this);
	connect (freqButton, SIGNAL (clicked (void)),
	         this, SLOT (handle_freqButton (void)));
//	set some sliders to their values
	k	= spectrumSettings -> value ("spectrumAmplitudeSlider", 20). toInt ();
	spectrumAmplitudeSlider	-> setValue (k);

	connect (zoomIn_Button, SIGNAL (clicked (void)),
	         this, SLOT (handle_zoomIn (void)));
	connect (zoomOut_Button, SIGNAL (clicked (void)),
	         this, SLOT (handle_zoomOut (void)));
	connect (reset_Button, SIGNAL (clicked (void)),
	         this, SLOT (handle_Reset (void)));
	displayRate	= 15;
	zoomFactor	= 1;
	stepSize	= theDevice -> getRate () / 1 / 100000;
	if (stepSize < 1)
	   stepSize = 1;
	zoomfactorDisplay	-> display (zoomFactor);
	stepSizeDisplay		-> display (stepSize);

//	just as a gadget, we show the actual time
	displayTimer		= new QTimer ();
	displayTimer		-> setInterval (1000);
	connect (displayTimer, SIGNAL (timeout ()),
	         this, SLOT (updateTimeDisplay ()));

	QString t = QString ("spectrumviewer ");
	t. append ("0.1");
//	systemindicator		-> setText (t);
	displayTimer		-> start (1000);
	fft_vector  = (std::complex<float> *)
                  fftwf_malloc (sizeof (std::complex<float>) * FFT_SIZE);
        plan    = fftwf_plan_dft_1d (FFT_SIZE,
                                    reinterpret_cast <fftwf_complex *>(fft_vector),
                                    reinterpret_cast <fftwf_complex *>(fft_vector),
                                    FFTW_FORWARD, FFTW_ESTIMATE);

	windowSize	= inputRate / displayRate < FFT_SIZE ?
	                     inputRate / displayRate : FFT_SIZE;
//	Blackman window
	for (int i = 0; i < windowSize; i ++) 
	   Window [i] = (0.42 -
                        0.5 * cos (2 * M_PI * (float)i / windowSize) +
                        0.08 * cos (4 * M_PI * (float)i / windowSize));

//	all elements seem to exist: set the control state to
//	its default values
	running. store (false);
	setStart ();
}

	Viewer::~Viewer (void) {
//	On normal program exit, we save some of the values
	spectrumSettings -> setValue ("currentFrequency",
	                                     (int)theDevice -> getVFOFrequency () / KHz (1));
	spectrumSettings -> setValue ("spectrumAmplitudeSlider",
	                              spectrumAmplitudeSlider -> value ());

	delete theDevice;
//	and then we delete
	delete		HF_Scope_1;
	delete		HF_Scope_2;
	delete		displayTimer;
	fftwf_destroy_plan (plan);
	fftwf_free	(fft_vector);
}

deviceHandler	*Viewer::setDevice (void) {
deviceHandler	*theDevice;
#ifdef	HAVE_SDRPLAY
	try {
	   theDevice	= new sdrplayHandler (spectrumSettings);
	   return theDevice;
	} catch (int e) {
	}
#endif
#ifdef	HAVE_LIME
	try {
	   theDevice	= new limeHandler (spectrumSettings);
	   return theDevice;
	} catch (int e) {
	}
#endif
#ifdef	HAVE_RTLSDR
	try {
	   theDevice	= new rtlsdrHandler (spectrumSettings);
	   return theDevice;
	} catch (int e) {
	}
#endif
#ifdef	HAVE_AIRSPY
	try {
	   theDevice	= new airspyHandler (spectrumSettings);
	   return theDevice;
	} catch (int e) {
	}
#endif
#ifdef	HAVE_HACKRF
	try {
	   theDevice	= new hackrfHandler (spectrumSettings);
	   return theDevice;
	} catch (int e) {
	}
#endif
	fprintf (stderr, "Sorry, no device found, fatal\n");
	throw (11);
}

void	Viewer::handle_zoomIn	(void) {
	if (FFT_SIZE / zoomFactor > displaySize)
	   zoomFactor ++;
	stepSize	= theDevice -> getRate () / zoomFactor / 100000;
	if (stepSize < 1)
	   stepSize = 1;
	stepSizeDisplay		-> display (stepSize);
	zoomfactorDisplay	-> display (zoomFactor);
}

void	Viewer::handle_zoomOut	(void) {
	if (zoomFactor > 1)
	   zoomFactor --;
	stepSize        = theDevice -> getRate () / zoomFactor / 100000;
	if (stepSize < 1)
	   stepSize = 1;
        stepSizeDisplay		-> display (stepSize);
	zoomfactorDisplay	-> display (zoomFactor);
}

void	Viewer::handle_Reset	(void) {
	if (zoomFactor == 1)
	   return;
	zoomFactor = 1;
	stepSize	= theDevice -> getRate () / 1 / 100000;
	stepSizeDisplay		-> display (stepSize);
	zoomfactorDisplay	-> display (zoomFactor);
}

void	Viewer::setStart (void) {
	if (running. load ())
	   setStop ();
//
//	parameters to use a bandwidth, frequency and decimation
//	to be done,
	Display (theDevice -> getVFOFrequency () / KHz (1));
	lcd_rate_display	-> display (theDevice -> getRate ());
	bool r = theDevice	-> restartReader ();
	if (!r) {
	   QMessageBox::warning (this, tr ("sdr"),
	                               tr ("Opening  device failed\n"));
	   exit (102);
	}
//	and we are on the move, so let the timer run
	running. store (true);
}

void	Viewer::setStop	(void) {
	if (!running. load ())
	   return;
	theDevice	-> stopReader ();
	running. store (false);
}

void	Viewer::TerminateProcess () {
	setStop ();
	accept ();
	delete	theDevice;
	qDebug () <<  "End of termination procedure";
}

void	Viewer::adjustFrequency (int n) {
	fprintf (stderr, "adjusting met %d KHz\n", n);
	setTuner (theDevice -> getVFOFrequency () + (uint64_t)(KHz (n)));
	Display (theDevice -> getVFOFrequency () / KHz (1));
}

//	SetTuner accepts freq in Hz.
//
void	Viewer::setTuner (uint64_t n) {
	fprintf (stderr, "setting tuner to %f\n", (float_type)n);
	theDevice	-> setVFOFrequency (n);
	Display ((int)(n / KHz (1)));
}

void	Viewer::newFrequency	(qint64 n) {
	setTuner ((uint64_t)n);
}
//
//	
void	Viewer::updateTimeDisplay (void) {
QDateTime	currentTime = QDateTime::currentDateTime ();

	timeDisplay	-> setText (currentTime.
	                            toString (QString ("dd.MM.yy:hh:mm:ss")));
}

//	we want to process inputRate / 10 length  segments,
//	which may amount to up to 800000 samples,
//	so the _I_Buffer should be large enough.
void	Viewer::handleSamples (void) {
double	Y_axis [displaySize];
double showDisplay [displaySize];
int	range	= theDevice -> getRate () / zoomFactor;
int	binSize	= theDevice -> getRate () / FFT_SIZE;
int64_t	currentFrequency	= theDevice -> getVFOFrequency ();
	if (!running. load ())
	   return;

	if (theDevice -> Samples () < windowSize)
	   return;

	if (windowSize < FFT_SIZE) {
	   theDevice	-> getSamples (fft_vector, windowSize);
	   for (int i = windowSize; i < FFT_SIZE; i ++)
	      fft_vector [i] = std::complex<float> (0, 0);
	}
	else
	   theDevice	-> getSamples (fft_vector, FFT_SIZE);

	theDevice	-> resetBuffer ();

	for (int i = 0; i < windowSize; i ++)
	   fft_vector [i] =
	         std::complex<float> (real (fft_vector [i]) * Window [i],
	                              imag (fft_vector [i]) * Window [i]);
	fftwf_execute (plan);
//
	int	segmentSize = FFT_SIZE / zoomFactor;
	for (int i = - displaySize / 2; i < displaySize / 2; i ++) {
	   Y_axis [i + displaySize / 2] = 0;
	   for (int j = 0; j < segmentSize / displaySize; j ++)
	      Y_axis [i + displaySize / 2] +=
	        abs (fft_vector [(FFT_SIZE + i * segmentSize / displaySize + j) % FFT_SIZE]);
	   Y_axis [i + displaySize / 2] /= segmentSize / displaySize;
	}
	bandwidthDisplay	-> display (range / KHz (1));
	HF_Scope_1	-> showFrame (Y_axis, range , currentFrequency,
	                              spectrumAmplitudeSlider -> value ());
	HF_Scope_2	-> showFrame (Y_axis, range, currentFrequency,
	                              spectrumAmplitudeSlider -> value ());
}

//	For displaying values, we use different scales, depending
//	on the size of the value
static inline
int32_t numberofDigits (uint64_t f) {

	if (f < 100000)
	   return 6;
	if (f < 100000000)
	   return 8;
	if (f < 1000000000)
	   return 9;
	else
	   return 10;
}

void	Viewer::Display (int32_t freq) {
int32_t nd	= numberofDigits (freq);
	lcd_freq_display	-> setDigitCount (nd);
	lcd_freq_display	-> display (freq);
}

void    Viewer::handle_freqButton (void) {
        if (mykeyPad -> isVisible ())
           mykeyPad -> hidePad ();
        else
           mykeyPad     -> showPad ();
}
//
//      Whenever the mousewheel is changed, the frequency
//      is adapted
void    Viewer::wheelEvent (QWheelEvent *e) {
	
        if (e -> delta () > 0)
           adjustFrequency (stepSize);
        else
           adjustFrequency (-stepSize);
}

#include <QCloseEvent>
void Viewer::closeEvent (QCloseEvent *event) {

        QMessageBox::StandardButton resultButton =
                        QMessageBox::question (this, "spectrumViewer",
                                               tr("Are you sure?\n"),
                                               QMessageBox::No | QMessageBox::Yes,
                                               QMessageBox::Yes);
        if (resultButton != QMessageBox::Yes) {
           event -> ignore();
        } else {
           TerminateProcess ();
           event -> accept ();
        }
}

/////////////////////////////////////////////////////////////////////////
//
