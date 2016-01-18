/*
 /***************************************************************************
 *
 * Author: "Sjors H.W. Scheres"
 * MRC Laboratory of Molecular Biology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * This complete copyright notice must be included in any revised version of the
 * source code. Additional authorship citations may be added, but existing
 * author citations must be preserved.
 ***************************************************************************/

#ifndef MOTIONCORR_RUNNER_H_
#define MOTIONCORR_RUNNER_H_

#include  <glob.h>
#include  <vector>
#include  <string>
#include  <stdlib.h>
#include  <stdio.h>
#include <src/time.h>
#include "src/metadata_table.h"

class MotioncorrRunner
{
public:

	// I/O Parser
	IOParser parser;

	// Verbosity
	int verb;

	// Output rootname
	FileName fn_in, fn_out, fn_movie;

	// Filenames of all the micrographs to run Motioncorr on
	std::vector<FileName> fn_micrographs;

	// First and last movie frames to use in alignment and written-out corrected average and movie (default: do all)
	int first_frame_ali, last_frame_ali, first_frame_sum, last_frame_sum;

	// Binning factor for binning inside MOTIONCORR
	int bin_factor;

	// Also save the aligned movies?
	bool do_save_movies;

	// Additional arguments that need to be passed to MOTIONCORR
	FileName fn_other_args;

	// MOTIONCORR executable
	FileName fn_motioncorr_exe;

	// Continue an old run: only estimate CTF if logfile WITH Final Values line does not yet exist, otherwise skip the micrograph
	bool continue_old;

	// Output STAR file
	MetaDataTable MDout;

public:
	// Read command line arguments
	void read(int argc, char **argv, int rank = 0);

	// Print usage instructions
	void usage();

	// Initialise some stuff after reading
	void initialise();

	// Execute all MOTIONCORR jobs
	void run();

	// Given an input fn_mic filename, this function will determine the names of the output corrected image (fn_avg) and the corrected movie (fn_mov).
	void getOutputFileNames(FileName fn_mic, FileName &fn_avg, FileName &fn_mov);

	// Execute MOTIONCORR for a single micrograph
	void executeMotioncorr(FileName fn_mic, int rank = 0);

	// Write out final STAR file
	void writeSTAR();

};


#endif /* MOTIONCORR_RUNNER_H_ */