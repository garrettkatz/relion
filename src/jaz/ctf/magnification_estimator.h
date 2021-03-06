/***************************************************************************
 *
 * Author: "Jasenko Zivanov"
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

#ifndef MAG_ESTIMATOR_H
#define MAG_ESTIMATOR_H

#include <vector>
#include <string>

#include <src/complex.h>
#include <src/image.h>

class IOParser;
class ReferenceMap;
class ObservationModel;
class MetaDataTable;

class MagnificationEstimator
{
	public:
		
		MagnificationEstimator();
		
		void read(IOParser& parser, int argc, char *argv[]);
		
		void init(
				int verb, int s, int nr_omp_threads,
				bool debug, bool diag, std::string outPath,
				ReferenceMap* reference, ObservationModel* obsModel);
		
		// Compute per-pixel information for one micrograph
		void processMicrograph(
				long g, MetaDataTable& mdt, 
				const std::vector<Image<Complex>>& obs,
				const std::vector<Image<Complex>>& pred);
		
		// Sum up per-pixel information from all micrographs, 
		// then fit beam-tilt model to the per-pixel fit
		void parametricFit(
				const std::vector<MetaDataTable>& mdts, 
				MetaDataTable& mdtOut);
		
		// Has this mdt been processed already?
		bool isFinished(const MetaDataTable& mdt);
		
		
	private:
				
		// cmd. line options (see read())
		double kmin;
		
		// parameters obtained through init()
		int verb, s, sh, nr_omp_threads;
		bool debug, diag, ready;
		std::string outPath;
		double angpix;
		
		ReferenceMap* reference;
		ObservationModel* obsModel;
};

#endif
