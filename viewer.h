#
/*
 *    Copyright (C)  2010, 2011, 2012
 *    Jan van Katwijk (J.vanKatwijk@gmail.com)
 *    Lazy Chair Computing
 *
 *    This file is part of the SDR-J.
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

#ifndef __VIEWER__
#define __VIEWER__

#include	<QDialog>
#include	"ui_sdrgui.h"
#include	<qwt.h>
#include	<qwt_slider.h>
#include	<qwt_plot.h>
#include	<qwt_plot_curve.h>
#include	<qwt_plot_marker.h>
#include	<qwt_plot_grid.h>
#include	<qwt_dial.h>
#include	<qwt_plot_spectrogram.h>
#include	<QTimer>
#include	<QWheelEvent>
#include	<atomic>
#include	<complex>
#include	<fftw3.h>
#include	"spectrum-scope.h"
#include	"waterfall-scope.h"
#include	<QCloseEvent>
//
#include	<QObject>

class	QSettings;
class	deviceHandler;
class	keyPad;
/*
 *	The main gui object. It inherits from
 *	QDialog and the generated form
 */
class Viewer: public QDialog,
		      private Ui_SDRplayViewer {
Q_OBJECT
public:
		Viewer	(QSettings *, QWidget *parent = NULL);
		~Viewer	(void);

private:
	QSettings	*spectrumSettings;
	spectrumScope	*HF_Scope_1;
	waterfallScope	*HF_Scope_2;
	int32_t		inputRate;
	int32_t		displaySize;
	int16_t		displayRate;
	int16_t		rasterSize;
	int32_t		spectrumSize;
	int		zoomFactor;
	int		stepSize;
	int		windowSize;
	std::atomic<bool>	running;
	deviceHandler	*theDevice;
	keyPad		*mykeyPad;
	void		setTuner		(uint64_t);
	QTimer		*displayTimer;
	int64_t		Panel;
	uint8_t		runMode;
	fftwf_plan	plan;
	std::complex<float> *fft_vector;
	deviceHandler	*setDevice		(void);
/*
 */
private slots:
	void	handle_zoomIn		(void);
	void	handle_zoomOut		(void);
	void	handle_Reset		(void);
	void	setStart		(void);
	void	setStop			(void);
	void	handle_freqButton	(void);
	void	updateTimeDisplay	(void);
	void	adjustFrequency		(int);

	void	TerminateProcess	(void);
	void	Display			(int32_t);
public slots:
	void	newFrequency		(qint64);
	void	handleSamples		(void);
	void	closeEvent		(QCloseEvent *event);
        void    wheelEvent              (QWheelEvent *);
};

#endif

