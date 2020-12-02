/*
*  Copyright (C) 2007 Teviet Creighton
*
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with with program; see the file COPYING. If not, write to the
*  Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston,
*  MA  02111-1307  USA
*/

/**
 * \file
 * \ingroup GenerateTaylorCW_h
 * \author Creighton, T. D.
 *
 * \brief Generates a quasiperiodic waveform.
 *
 * ### Usage ###
 *
 * \code
 * SimulateTaylorCWTest [-s sourcefile] [-r respfile] [-l site earthfile sunfile]
 * [-o outfile] [-t sec nsec npt dt] [-h hsec hnsec fh]
 * [-d debuglevel]
 * \endcode
 *
 * ### Description ###
 *
 * This program generates a Taylor-parameterized continuous waveform as a
 * function of time.  The following option flags are accepted:
 * <ul>
 * <li>[<tt>-s</tt>] Reads source information from the file
 * \c sourcefile, whose format is specified below.  If absent, it
 * injects a monochromatic wave with intrinsic frequency 100~Hz, strain
 * amplitude 1000, and zero phase at the GPS epoch, arriving from the
 * direction RA=00h00m, dec=\f$0^\circ\f$.</li>
 * <li>[<tt>-r</tt>] Reads a detector response function from the file
 * \c respfile, whose format is specified below.  If absent, it
 * generates raw dimensionless strain.</li>
 * <li>[<tt>-l</tt>] Sets the detector location and orientation.
 * \c site must be one of the following character strings:
 * \c LHO, \c LLO, \c VIRGO, \c GEO600, \c TAMA300,
 * or \c CIT40.  \c earthfile and \c sunfile are ephemeris
 * files of the format expected by <tt>LALInitBarycenter()</tt>.  If the
 * <tt>-l</tt> option is not specified, a stationary (barycentric) detector
 * aligned with the wave's + polarization is assumed.</li>
 * <li>[<tt>-o</tt>] Writes the generated time series to the file
 * \c outfile.  If absent, the routines are exercised, but no output
 * is written.</li>
 * <li>[<tt>-t</tt>] Sets the timing information for the generated
 * waveform: \c sec and \c nsec are integers specifying the start
 * time in GPS seconds and nanoseconds, \c npt is the number of time
 * samples generated, and \c dt is the sampling interval in seconds.
 * If absent, <tt>-t 0 0 65536 9.765625e-4</tt> is assumed.</li>
 * <li>[<tt>-h</tt>] Performs "ideal heterodyning" (phase subtraction)
 * on the signal: \c hsec and \c hnsec are integers specifying an
 * epoch of zero phase subtraction in GPS seconds and nanoseconds, and
 * \c fh is the frequency of phase subtraction in Hz.  If absent, no
 * heterodyning is performed.</li>
 * <li>[<tt>-d</tt>] Sets the debug level to \c debuglevel.  If
 * absent, level 0 is assumed.</li>
 * </ul>
 *
 * \par Format for \c sourcefile:
 * The source file consists
 * of any number of lines of data, each specifying a continuous waveform.
 * Each line consists of a GPS epoch where the frequency, phase, and
 * Taylor coefficients are defined (\c INT8 nanoseconds), followed by
 * 7 or more whitespace-delimited \c REAL8 numbers: the + and
 * \f$\times\f$ wave amplitudes (dimensionless strain) and polarization angle
 * \f$\psi\f$ (degrees), the right ascension and declination (degrees), the
 * initial phase (degrees) and frequency (Hz), followed by zero or more
 * Taylor coefficients \f$f_k\f$ (Hz\f${}^k\f$).  Note that the wave amplitudes
 * and polarization angle are read as \c REAL8, but are later cast to
 * \c REAL4.
 *
 * \par Format for \c respfile:
 * The response function \f$R(f)\f$
 * gives the real and imaginary components of the transformation
 * \e from ADC output \f$o\f$ \e to tidal strain \f$h\f$ via
 * \f$\tilde{h}(f)=R(f)\tilde{o}(f)\f$.  It is inverted internally to give
 * the detector <em>transfer function</em> \f$T(f)=1/R(f)\f$.  The format
 * \c respfile is a header specifying the GPS epoch \f$t_0\f$ at which
 * the response was taken (\c INT8 nanoseconds), the lowest frequency
 * \f$f_0\f$ at which the response is given (\c REAL8 Hz), and the
 * frequency sampling interval \f$\Delta f\f$ (\c REAL8 Hz):
 *
 * <table><tr><td>
 * <tt># epoch = </tt>\f$t_0\f$</td></tr>
 * <tr><td><tt># f0 = </tt>\f$f_0\f$</td></tr>
 * <tr><td><tt># deltaF = </tt>\f$\Delta f\f$
 * </td></tr></table>
 *
 * followed by two columns of \c REAL4 data giving the real
 * and imaginary components of \f$R(f_0+k\Delta f)\f$.
 *
 * \par Format for \c outfile:
 * The ouput files generated by
 * this program consist of a two-line header giving the GPS epoch \f$t_0\f$
 * of the first time sample (\c INT8 nanoseconds) and the sampling
 * interval \f$\Delta t\f$ (\c REAL8 seconds):
 *
 * <table><tr><td>
 * <tt># epoch = </tt>\f$t_0\f$</td></tr>
 * <tr><td><tt># deltaT = </tt>\f$\Delta t\f$
 * </td></tr></table>
 *
 * followed by a single column of \c REAL4 data
 * representing the undigitized output of the interferometer's
 * gravitational-wave channel.
 *
 * ### Algorithm ###
 *
 * If a \c sourcefile is specified, this program first reads the
 * epoch field, and then calls <tt>LALSReadVector()</tt> to read the
 * remaining fields.  (If no \c sourcefile is specified, the
 * parameters are taken from <tt>\#define</tt>d constants.) The arguments
 * are passed to <tt>LALGenerateTaylorCW()</tt> to generate frequency and
 * phase timeseries.  The required sampling resolution for these
 * timeseries is estimated at \f$0.1/\sum_k\sqrt{|kf_0f_kT^{k-1}|}\f$, where
 * \f$T\f$ is the duration of the waveform, to ensure that later
 * interpolation of the waveforms will give phases accurate to well
 * within a radian.
 *
 * The output from <tt>LALGenerateTaylorCW()</tt> is then passed to
 * <tt>LALPulsarSimulateCoherentGW()</tt> to generate an output time series.  If
 * there are multiple lines in \c sourcefile, the procedure is
 * repeated and the new waveforms added into the output.  A warning is
 * generated if the wave frequency exceeds the Nyquist rate for the
 * output time series.
 *
 */

/** \name Error Codes */
/** @{ */
#define SIMULATETAYLORCWTESTC_ENORM  0	/**< Normal exit */
#define SIMULATETAYLORCWTESTC_ESUB   1	/**< Subroutine failed */
#define SIMULATETAYLORCWTESTC_EARG   2	/**< Error parsing arguments */
#define SIMULATETAYLORCWTESTC_EVAL   3	/**< Input argument out of valid range */
#define SIMULATETAYLORCWTESTC_EFILE  4	/**< Could not open file */
#define SIMULATETAYLORCWTESTC_EINPUT 5	/**< Error reading file */
#define SIMULATETAYLORCWTESTC_EMEM   6	/**< Out of memory */
#define SIMULATETAYLORCWTESTC_EPRINT 7	/**< Wrote past end of message string */
/** @} */

/** \cond DONT_DOXYGEN */
#define SIMULATETAYLORCWTESTC_MSGENORM  "Normal exit"
#define SIMULATETAYLORCWTESTC_MSGESUB   "Subroutine failed"
#define SIMULATETAYLORCWTESTC_MSGEARG   "Error parsing arguments"
#define SIMULATETAYLORCWTESTC_MSGEVAL   "Input argument out of valid range"
#define SIMULATETAYLORCWTESTC_MSGEFILE  "Could not open file"
#define SIMULATETAYLORCWTESTC_MSGEINPUT "Error reading file"
#define SIMULATETAYLORCWTESTC_MSGEMEM   "Out of memory"
#define SIMULATETAYLORCWTESTC_MSGEPRINT "Wrote past end of message string"


#include <math.h>
#include <stdlib.h>
#include <lal/LALStdio.h>
#include <lal/LALStdlib.h>
#include <lal/LALConstants.h>
#include <lal/StreamInput.h>
#include <lal/AVFactories.h>
#include <lal/SeqFactories.h>
#include <lal/VectorOps.h>
#include <lal/DetectorSite.h>
#include <lal/Units.h>
#include <lal/PulsarSimulateCoherentGW.h>
#include <lal/GenerateTaylorCW.h>
#include <lal/LALBarycenter.h>
#include <lal/LALInitBarycenter.h>

/* Default parameter settings. */
#define EPOCH  (0LL) /* about Jan. 1, 1990 */
#define APLUS  (1000.0)
#define ACROSS (1000.0)
#define RA     (0.0)
#define DEC    (0.0)
#define PSI    (0.0)
#define F0     (100.0)
#define FH     (0.0)
#define PHI0   (0.0)
#define SEC    (0)
#define NSEC   (0)
#define HSEC   (0)
#define HNSEC  (0)
#define DT     (0.0009765625)
#define NPT    (65536)

/* Usage format string. */
#define USAGE "Usage: %s [-s sourcefile] [-o outfile] [-r respfile]\n" \
"\t[-l site earthfile sunfile] [-o outfile] [-t sec nsec npt dt]\n"    \
"\t[-t hsec hnsec fh] [-d debuglevel]\n"

/* Maximum output message length. */
#define MSGLEN (1024)

/* Upper cutoff frequency for default detector response function. */
#define FSTOP (16384.0)

/* Macros for printing errors and testing subroutines. */
#define ERROR( code, msg, statement )                                \
do                                                                   \
if ( lalDebugLevel & LALERROR )                                      \
{                                                                    \
  XLALPrintError( "Error[0] %d: program %s, file %s, line %d, %s\n"   \
		 "        %s %s\n", (code), *argv, __FILE__,         \
		 __LINE__, "$Id$",                    \
		 statement ? statement : "", (msg) );                \
}                                                                    \
while (0)

#define INFO( statement )                                            \
do                                                                   \
if ( lalDebugLevel & LALINFO )                                       \
{                                                                    \
  XLALPrintError( "Info[0]: program %s, file %s, line %d, %s\n"       \
		 "        %s\n", *argv, __FILE__, __LINE__,          \
		 "$Id$", (statement) );               \
}                                                                    \
while (0)

#define WARNING( statement )                                         \
do                                                                   \
if ( lalDebugLevel & LALWARNING )                                    \
{                                                                    \
  XLALPrintError( "Warning[0]: program %s, file %s, line %d, %s\n"    \
		 "        %s\n", *argv, __FILE__, __LINE__,          \
		 "$Id$", (statement) );               \
}                                                                    \
while (0)

#define SUB( func, statusptr )                                       \
do                                                                   \
if ( (func), (statusptr)->statusCode )                               \
{                                                                    \
  ERROR( SIMULATETAYLORCWTESTC_ESUB, SIMULATETAYLORCWTESTC_MSGESUB,  \
	 "Function call \"" #func "\" failed:" );                    \
  return SIMULATETAYLORCWTESTC_ESUB;                                 \
}                                                                    \
while (0)

#define CHECKVAL( val, lower, upper )                                \
do                                                                   \
if ( ( (val) < (lower) ) || ( (val) > (upper) ) )                    \
{                                                                    \
  ERROR( SIMULATETAYLORCWTESTC_EVAL, SIMULATETAYLORCWTESTC_MSGEVAL,  \
         "Value of " #val " out of range:" );                        \
  if ( lalDebugLevel & LALERROR )                                    \
    XLALPrintError( #val " = %f, range = [%f,%f]\n", (REAL8)(val),    \
                   (REAL8)(lower), (REAL8)(upper) );                 \
  return SIMULATETAYLORCWTESTC_EVAL;                                 \
}                                                                    \
while (0)

/* A function to convert INT8 nanoseconds to LIGOTimeGPS. */
void
I8ToLIGOTimeGPS( LIGOTimeGPS *output, INT8 input );

/* A function to compute the combination function C(a+1,b+1). */
UINT4
choose( UINT4 a, UINT4 b );


int
main(int argc, char **argv)
{
  /* Command-line parsing variables. */
  int arg;                         /* command-line argument counter */
  static LALStatus stat;           /* status structure */
  CHAR *sourcefile = NULL;         /* name of sourcefile */
  CHAR *respfile = NULL;           /* name of respfile */
  CHAR *outfile = NULL;            /* name of outfile */
  CHAR *earthfile = NULL;          /* name of earthfile */
  CHAR *sunfile = NULL;            /* name of sunfile */
  CHAR *site = NULL;               /* name of detector site */
  INT4 npt = NPT;                  /* number of output samples */
  INT4 sec = SEC, nsec = NSEC;     /* GPS epoch of output */
  INT4 hsec = HSEC, hnsec = HNSEC; /* GPS heterodyning epoch */
  REAL8 dt = DT;                   /* output sampling interval */
  REAL8 fh = FH;                   /* heterodyning frequency */

  /* File reading variables. */
  FILE *fp = NULL;    /* generic file pointer */
  BOOLEAN ok = 1;     /* whether input format is correct */
  INT8 epoch = EPOCH; /* epoch stored as an INT8 */

  /* Other variables. */
  UINT4 i, j;                /* generic indecies */
  INT8 tStart, tStop;        /* start and stop times for waveform */
  PulsarDetectorResponse detector; /* the detector in question */
  REAL4TimeSeries output;    /* detector output */


  /*******************************************************************
   * ARGUMENT PARSING (arg stores the current position)              *
   *******************************************************************/

  arg = 1;
  while ( arg < argc ) {
    /* Parse source file option. */
    if ( !strcmp( argv[arg], "-s" ) ) {
      if ( argc > arg + 1 ) {
	arg++;
	sourcefile = argv[arg++];
      } else {
	ERROR( SIMULATETAYLORCWTESTC_EARG,
	       SIMULATETAYLORCWTESTC_MSGEARG, 0 );
        XLALPrintError( USAGE, *argv );
        return SIMULATETAYLORCWTESTC_EARG;
      }
    }
    /* Parse response file option. */
    else if ( !strcmp( argv[arg], "-r" ) ) {
      if ( argc > arg + 1 ) {
	arg++;
	respfile = argv[arg++];
      } else {
	ERROR( SIMULATETAYLORCWTESTC_EARG,
	       SIMULATETAYLORCWTESTC_MSGEARG, 0 );
        XLALPrintError( USAGE, *argv );
        return SIMULATETAYLORCWTESTC_EARG;
      }
    }
    /* Parse output file option. */
    else if ( !strcmp( argv[arg], "-o" ) ) {
      if ( argc > arg + 1 ) {
	arg++;
	outfile = argv[arg++];
      } else {
	ERROR( SIMULATETAYLORCWTESTC_EARG,
	       SIMULATETAYLORCWTESTC_MSGEARG, 0 );
        XLALPrintError( USAGE, *argv );
        return SIMULATETAYLORCWTESTC_EARG;
      }
    }
    /* Parse detector location option. */
    else if ( !strcmp( argv[arg], "-l" ) ) {
      if ( argc > arg + 3 ) {
	arg++;
	site = argv[arg++];
	earthfile = argv[arg++];
	sunfile = argv[arg++];
      } else {
	ERROR( SIMULATETAYLORCWTESTC_EARG,
	       SIMULATETAYLORCWTESTC_MSGEARG, 0 );
        XLALPrintError( USAGE, *argv );
        return SIMULATETAYLORCWTESTC_EARG;
      }
    }
    /* Parse output timing option. */
    else if ( !strcmp( argv[arg], "-t" ) ) {
      if ( argc > arg + 4 ) {
	arg++;
	sec = atoi( argv[arg++] );
	nsec = atoi( argv[arg++] );
	npt = atoi( argv[arg++] );
	dt = atof( argv[arg++] );
      } else {
	ERROR( SIMULATETAYLORCWTESTC_EARG,
	       SIMULATETAYLORCWTESTC_MSGEARG, 0 );
        XLALPrintError( USAGE, *argv );
        return SIMULATETAYLORCWTESTC_EARG;
      }
    }
    /* Parse heterodyning option. */
    else if ( !strcmp( argv[arg], "-h" ) ) {
      if ( argc > arg + 4 ) {
	arg++;
	hsec = atoi( argv[arg++] );
	hnsec = atoi( argv[arg++] );
	fh = atof( argv[arg++] );
      } else {
	ERROR( SIMULATETAYLORCWTESTC_EARG,
	       SIMULATETAYLORCWTESTC_MSGEARG, 0 );
        XLALPrintError( USAGE, *argv );
        return SIMULATETAYLORCWTESTC_EARG;
      }
    }
    /* Parse debug level option. */
    else if ( !strcmp( argv[arg], "-d" ) ) {
      if ( argc > arg + 1 ) {
	arg++;
      }else{
	ERROR( SIMULATETAYLORCWTESTC_EARG,
	       SIMULATETAYLORCWTESTC_MSGEARG, 0 );
        XLALPrintError( USAGE, *argv );
        return SIMULATETAYLORCWTESTC_EARG;
      }
    }
    /* Check for unrecognized options. */
    else if ( argv[arg][0] == '-' ) {
      ERROR( SIMULATETAYLORCWTESTC_EARG,
	     SIMULATETAYLORCWTESTC_MSGEARG, 0 );
      XLALPrintError( USAGE, *argv );
      return SIMULATETAYLORCWTESTC_EARG;
    }
  } /* End of argument parsing loop. */

  /* Make sure that values won't crash the system or anything. */
  CHECKVAL( dt, LAL_REAL8_MIN, LAL_REAL8_MAX );
  CHECKVAL( npt, 0, 2147483647 );


  /*******************************************************************
   * SETUP                                                           *
   *******************************************************************/

  /* Set up output structure and wave start and stop times. */
  {
    INT8 epochOut = nsec;    /* output epoch */
    epochOut += 1000000000LL*sec;
    tStart = epochOut - 1000000000LL;
    memset( &output, 0, sizeof(REAL4TimeSeries) );
    I8ToLIGOTimeGPS( &(output.epoch), epochOut );
    output.deltaT = dt;
    snprintf( output.name, LALNameLength, "Taylor CW waveform" );
    SUB( LALSCreateVector( &stat, &(output.data), npt ), &stat );
    memset( output.data->data, 0, npt*sizeof(REAL4) );
    tStop = epochOut + 1000000000LL*(INT8)( dt*npt + 1.0 );
    output.f0 = fh;
  }
  /* Adjust wave start and stop times so that they will almost
     certainly cover the output timespan even after barycentring. */
  if ( site ) {
    tStart -= (INT8)( (1.1e9)*LAL_AU_SI/LAL_C_SI );
    tStop += (INT8)( (1.1e9)*LAL_AU_SI/LAL_C_SI );
  }


  /* Set up detector structure. */
  memset( &detector, 0, sizeof(PulsarDetectorResponse) );
  COMPLEX8FrequencySeries * transfer = (COMPLEX8FrequencySeries *)
    LALMalloc( sizeof(COMPLEX8FrequencySeries) );
  if ( !(transfer) ) {
    ERROR( SIMULATETAYLORCWTESTC_EMEM,
	   SIMULATETAYLORCWTESTC_MSGEMEM, 0 );
    return SIMULATETAYLORCWTESTC_EMEM;
  }
  detector.heterodyneEpoch.gpsSeconds = hsec;
  detector.heterodyneEpoch.gpsNanoSeconds = hnsec;
  memset( transfer, 0, sizeof(COMPLEX8FrequencySeries) );
  if ( respfile ) {
    REAL4VectorSequence *resp = NULL; /* response as vector sequence */
    COMPLEX8Vector *response = NULL;  /* response as complex vector */
    COMPLEX8Vector *unity = NULL;     /* vector of complex 1's */

    if ( ( fp = fopen( respfile, "r" ) ) == NULL ) {
      ERROR( SIMULATETAYLORCWTESTC_EFILE,
	     SIMULATETAYLORCWTESTC_MSGEFILE, respfile );
      return SIMULATETAYLORCWTESTC_EFILE;
    }

    /* Read header. */
    ok &= ( fscanf( fp, "# epoch = %" LAL_INT8_FORMAT "\n", &epoch ) == 1 );
    I8ToLIGOTimeGPS( &( transfer->epoch ), epoch );
    ok &= ( fscanf( fp, "# f0 = %lf\n", &( transfer->f0 ) )
            == 1 );
    ok &= ( fscanf( fp, "# deltaF = %lf\n",
                    &( transfer->deltaF ) ) == 1 );
    if ( !ok ) {
      ERROR( SIMULATETAYLORCWTESTC_EINPUT,
	     SIMULATETAYLORCWTESTC_MSGEINPUT, respfile );
      return SIMULATETAYLORCWTESTC_EINPUT;
    }

    /* Read and convert body to a COMPLEX8Vector. */
    SUB( LALSReadVectorSequence( &stat, &resp, fp ), &stat );
    fclose( fp );
    if ( resp->vectorLength != 2 ) {
      ERROR( SIMULATETAYLORCWTESTC_EINPUT,
	     SIMULATETAYLORCWTESTC_MSGEINPUT, respfile );
      return SIMULATETAYLORCWTESTC_EINPUT;
    }
    SUB( LALCCreateVector( &stat, &response, resp->length ), &stat );
    memcpy( response->data, resp->data, 2*resp->length*sizeof(REAL4) );
    SUB( LALSDestroyVectorSequence( &stat, &resp ), &stat );

    /* Convert response function to a transfer function. */
    SUB( LALCCreateVector( &stat, &unity, response->length ), &stat );
    for ( i = 0; i < response->length; i++ ) {
      unity->data[i] = 1.0;
    }
    SUB( LALCCreateVector( &stat, &( transfer->data ),
                           response->length ), &stat );
    SUB( LALCCVectorDivide( &stat, transfer->data, unity,
                            response ), &stat );
    SUB( LALCDestroyVector( &stat, &response ), &stat );
    SUB( LALCDestroyVector( &stat, &unity ), &stat );
  }
  /* No response file, so generate a unit response. */
  else {
    I8ToLIGOTimeGPS( &( transfer->epoch ), EPOCH );
    transfer->f0 = 0.0;
    transfer->deltaF = FSTOP;
    SUB( LALCCreateVector( &stat, &( transfer->data ), 2 ),
         &stat );
    transfer->data->data[0] = 1.0;
    transfer->data->data[1] = 1.0;
  }
  LALDetector *lsite = NULL;
  EphemerisData *lephem = NULL;
  if ( site ) {
    /* Set detector location. */
    if ( !strcmp( site, "LHO" ) )
      i = LALDetectorIndexLHODIFF;
    else if ( !strcmp( site, "LLO" ) )
      i = LALDetectorIndexLLODIFF;
    else if ( !strcmp( site, "VIRGO" ) )
      i = LALDetectorIndexVIRGODIFF;
    else if ( !strcmp( site, "GEO600" ) )
      i = LALDetectorIndexGEO600DIFF;
    else if ( !strcmp( site, "TAMA300" ) )
      i = LALDetectorIndexTAMA300DIFF;
    else if ( !strcmp( site, "CIT40" ) )
      i = LALDetectorIndexCIT40DIFF;
    else {
      ERROR( SIMULATETAYLORCWTESTC_EVAL,
	     SIMULATETAYLORCWTESTC_MSGEVAL, "Unrecognized site:" );
      if ( lalDebugLevel & LALERROR )
	XLALPrintError( "%s", site );
      return SIMULATETAYLORCWTESTC_EVAL;
    }
    lsite = (LALDetector *)LALMalloc( sizeof(LALDetector) );
    if ( !(lsite) ) {
      ERROR( SIMULATETAYLORCWTESTC_EMEM,
	     SIMULATETAYLORCWTESTC_MSGEMEM, 0 );
      return SIMULATETAYLORCWTESTC_EMEM;
    }
    *(lsite) = lalCachedDetectors[i];

    /* Read ephemerides. */
    XLAL_CHECK_MAIN( ( lephem = XLALInitBarycenter( earthfile, sunfile ) ) != NULL, XLAL_EFUNC );
  }


  /* Set up units for the above structures. */
  output.sampleUnits = lalADCCountUnit;
  if (XLALUnitDivide( &(transfer->sampleUnits),
                      &lalADCCountUnit, &lalStrainUnit ) == NULL) {
    return LAL_EXLAL;
  }

  detector.transfer = transfer;
  detector.site = lsite;
  detector.ephemerides = lephem;

  /*******************************************************************
   * OUTPUT GENERATION                                               *
   *******************************************************************/

  /* Open sourcefile. */
  if ( sourcefile ) {
    if ( ( fp = fopen( sourcefile, "r" ) ) == NULL ) {
      ERROR( SIMULATETAYLORCWTESTC_EFILE,
	     SIMULATETAYLORCWTESTC_MSGEFILE, sourcefile );
      return SIMULATETAYLORCWTESTC_EFILE;
    }
  }

  /* For each line in the sourcefile... */
  while ( ok ) {
    TaylorCWParamStruc params; /* wave generation parameters */
    PulsarCoherentGW waveform;       /* amplitude and phase structure */
    REAL4TimeSeries signalvec;    /* GW signal */
    CHAR message[MSGLEN];      /* warning/info messages */

    /* Initialize output structures. */
    memset( &waveform, 0, sizeof(PulsarCoherentGW) );
    signalvec = output;
    signalvec.data = NULL;

    /* Read and convert input line. */
    memset( &params, 0, sizeof(TaylorCWParamStruc) );
    I8ToLIGOTimeGPS( &(params.epoch), tStart );
    params.position.system = COORDINATESYSTEM_EQUATORIAL;
    if ( sourcefile ) {
      REAL8Vector *input = NULL; /* input parameters */
      ok &= ( fscanf( fp, "%" LAL_INT8_FORMAT, &epoch ) == 1 );
      if ( ok ) {
	SUB( LALDReadVector( &stat, &input, fp, 1 ), &stat );
	ok &= ( input->length > 6 );
      }
      if ( ok ) {
	params.aPlus = input->data[0];
	params.aCross = input->data[1];
	params.psi = LAL_PI*input->data[2]/180.0;
	params.position.longitude = LAL_PI*input->data[3]/180.0;
	params.position.latitude = LAL_PI*input->data[4]/180.0;
	params.phi0 = LAL_PI*input->data[5]/180.0;
	params.f0 = input->data[6];
	if ( input->length > 7 ) {
	  SUB( LALDCreateVector( &stat, &(params.f),
				 input->length - 7 ), &stat );
	  for ( i = 0; i < input->length - 7; i++ )
	    params.f->data[i] = input->data[i+7];
	}
      }
      if ( input )
	SUB( LALDDestroyVector( &stat, &input ), &stat );
    } else {
      params.aPlus = APLUS;
      params.aCross = ACROSS;
      params.psi = PSI;
      params.position.longitude = RA;
      params.position.latitude = DEC;
      params.phi0 = PHI0;
      params.f0 = F0;
    }

    /* Adjust frequency and spindown terms to the actual wave start
       time. */
    if ( params.f ) {
      UINT4 length = params.f->length; /* number of coefficients */
      REAL8 t = (1.0e-9)*(REAL4)( tStart - epoch ); /* time shift */
      REAL8 tN = 1.0;   /* t raised to various powers */
      REAL8 fFac = 1.0; /* fractional change in frequency */
      REAL8 tFac = 1.0; /* time integral of fFac */
      REAL8 *fData = params.f->data; /* pointer to coeficients */
      for ( i = 0; i < length; i++ ) {
	REAL8 tM = 1.0; /* t raised to various powers */
	fFac += fData[i]*( tN *= t );
	tFac += fData[i]*tN/( i + 2.0 );
	for ( j = i + 1; j < length; j++ )
	  fData[i] += choose( j + 1, i + 1 )*fData[j]*( tM *= t );
      }
      params.phi0 += LAL_TWOPI*params.f0*t*tFac;
      params.f0 *= fFac;
      for ( i = 0; i < length; i++ )
	fData[i] /= fFac;
    }

    if ( ok ) {
      REAL4 *sigData, *outData; /* pointers to time series data */
      REAL4 t = (1.0e-9)*(REAL4)( tStop - tStart ); /* duration */
      REAL4 dtInv = 0.0; /* sampling rate for waveform */

      /* Set remaining parameters, and generate waveform. */
      if ( params.f ) {
	REAL4 tN = 1.0; /* t raised to various powers */
	for ( i = 0; i < params.f->length; i++ ) {
	  dtInv += sqrt( (i+1)*fabs( params.f->data[i] )*tN );
	  tN *= t;
	}
	dtInv *= 10.0*sqrt( fabs( params.f0 ) );
      }
      if ( dtInv < 1.0/t ) {
	params.deltaT = t;
	params.length = 2;
      } else {
	params.deltaT = 1.0/dtInv;
	params.length = (UINT4)( t*dtInv ) + 2;
      }
      SUB( LALGenerateTaylorCW( &stat, &waveform, &params ), &stat );
      if ( params.dfdt > 2.0 ) {
	/* snprintf() can't seem to print floating-point formats.
        snprintf( message, MSGLEN,
                     "Waveform sampling interval is too large:\n"
                     "\tmaximum df*dt = %f", params.dfdt );
	*/
	INT4 code = sprintf( message,
			     "Waveform sampling interval is too large:\n"
			     "\tmaximum df*dt = %f", params.dfdt );
	if ( code >= MSGLEN || code < 0 ) {
	  ERROR( SIMULATETAYLORCWTESTC_EPRINT,
		 SIMULATETAYLORCWTESTC_MSGEPRINT, 0 );
	  return SIMULATETAYLORCWTESTC_EPRINT;
	}
        WARNING( message );
      }
      SUB( LALSCreateVector( &stat, &(signalvec.data), npt ), &stat );
      SUB( LALPulsarSimulateCoherentGW( &stat, &signalvec, &waveform,
				  &detector ), &stat );
      if ( params.f )
	SUB( LALDDestroyVector( &stat, &(params.f) ), &stat );

      /* Inject waveform into output. */
      sigData = signalvec.data->data;
      outData = output.data->data;
      for ( i = 0; i < (UINT4)( npt ); i++ )
	outData[i] += sigData[i];

      /* Clean up memory. */
      SUB( LALSDestroyVectorSequence( &stat, &( waveform.a->data ) ),
           &stat );
      SUB( LALSDestroyVector( &stat, &( waveform.f->data ) ),
	   &stat );
      SUB( LALDDestroyVector( &stat, &( waveform.phi->data ) ),
	   &stat );
      LALFree( waveform.a );
      LALFree( waveform.f );
      LALFree( waveform.phi );
      SUB( LALSDestroyVector( &stat, &(signalvec.data) ), &stat );
    }

    /* Inject only one signal if there is no sourcefile. */
    if ( !sourcefile )
      ok = 0;
  }

  /* Input file is exhausted (or has a badly-formatted line ). */
  if ( sourcefile )
    fclose( fp );


  /*******************************************************************
   * CLEANUP                                                         *
   *******************************************************************/

  /* Print output file. */
  if ( outfile ) {
    if ( ( fp = fopen( outfile, "w" ) ) == NULL ) {
      ERROR( SIMULATETAYLORCWTESTC_EFILE,
	     SIMULATETAYLORCWTESTC_MSGEFILE, outfile );
      return SIMULATETAYLORCWTESTC_EFILE;
    }
    epoch = 1000000000LL*(INT8)( output.epoch.gpsSeconds );
    epoch += (INT8)( output.epoch.gpsNanoSeconds );
    fprintf( fp, "# epoch = %" LAL_INT8_FORMAT "\n", epoch );
    fprintf( fp, "# deltaT = %23.16e\n", output.deltaT );
    for ( i = 0; i < output.data->length; i++ )
      fprintf( fp, "%16.9e\n", (REAL4)( output.data->data[i] ) );
    fclose( fp );
  }

  /* Destroy remaining memory. */
  SUB( LALSDestroyVector( &stat, &( output.data ) ), &stat );
  SUB( LALCDestroyVector( &stat, &( transfer->data ) ),
       &stat );
  LALFree( transfer );
  if ( site ) {
    XLALDestroyEphemerisData( lephem );
    LALFree( lsite );
  }

  /* Done! */
  LALCheckMemoryLeaks();
  INFO( SIMULATETAYLORCWTESTC_MSGENORM );
  return SIMULATETAYLORCWTESTC_ENORM;
}


/* A function to convert INT8 nanoseconds to LIGOTimeGPS. */
void
I8ToLIGOTimeGPS( LIGOTimeGPS *output, INT8 input )
{
  INT8 s = input / 1000000000LL;
  output->gpsSeconds = (INT4)( s );
  output->gpsNanoSeconds = (INT4)( input - 1000000000LL*s );
  return;
}


/* A function to compute the combination function C(a,b). */
UINT4
choose( UINT4 a, UINT4 b )
{
  UINT4 numer = 1;
  UINT4 denom = 1;
  UINT4 lal_index = b + 1;
  while ( --lal_index ) {
    numer *= a - b + lal_index;
    denom *= lal_index;
  }
  return numer/denom;
}
/** \endcond */