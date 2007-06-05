// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//
// --------------------------------------------------------------------------
//                   OpenMS Mass Spectrometry Framework
// --------------------------------------------------------------------------
//  Copyright (C) 2003-2007 -- Oliver Kohlbacher, Knut Reinert
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// --------------------------------------------------------------------------
// $Maintainer: Eva Lange $
// --------------------------------------------------------------------------
//

#ifndef OPENMS_TRANSFORMATIONS_RAW2PEAK_PEAKSHAPE_H
#define OPENMS_TRANSFORMATIONS_RAW2PEAK_PEAKSHAPE_H

#include <math.h>

#include <OpenMS/CONCEPT/Types.h>
#include <OpenMS/KERNEL/PickedPeak1D.h>

namespace OpenMS
{

  /** @brief This class is a internal representation (used by the PeakPickerCWT) of a peak shape.

      It defines an asymmetric lorentzian and asymmetric hyperbolic squared secan function. 
  */

  class PeakShape
  {
  public:

    /// Constructor
    PeakShape()
        : height(0),
        mz_position(0),
        left_width(0),
        right_width(0),
        area(0),
        r_value(0),
        signal_to_noise(0.),
        type(PeakShapeType::UNDEFINED)
    {}
    /// Constructor
    PeakShape(double height_,
              double mz_position_,
              double left_width_,
              double right_width_,
              double area_,
              PeakShapeType::Enum type_);
    /// Copy constructor
    PeakShape(const PeakShape& peakshape);
    /// Destructor
    virtual ~PeakShape(){}
    /// Assignment operator
    PeakShape& operator = (const PeakShape& peakshape);

    /// Compute the intensity of the peaks shape at position x
    double operator() (double x) const;
    /// Computes symmetry measure of the peak shape, which is corresponds to th ratio of the left and right width parameters.
    double getSymmetricMeasure() const;
    /// Estimates the full width at half maximum.
    double getFWHM() const;
    /// Maximum intensity of the peak shape
    double height;
    /// Centroid position
    double mz_position;
    /// Left width parameter
    double left_width;
    /// Right width parameter
    double right_width;
    /// Area of the peak shape
    double area;
    /** @brief Correlation coefficient.
      
      It represents the squared pearson correlation coefficient with the original data (0 <= r_value <= 1).
    */
    double r_value;
    /// The signal to noise ratio at the mz_position
    double signal_to_noise;
    /** @brief Peak shape type (asymmetric lorentzian or asymmetric hyperbolic secans squared).

    *    The peak shape can represent an asymmetric lorentzian function, given by 
    
    *    l(x) = height/(1.+pow(left_width*(x - mz_position), 2)) (x<=mz_position) 
    
    *    l(x) = height/(1.+pow(right_width*(x - mz_position), 2)) (x>mz_position)
        
    *    or an asymmetric hyperbolic secans squared function 
    
    *   s(x) = height/pow(cosh(left_width*(x-mz_position)), 2) (x<=mz_position)
    
    *   s(x) = height/pow(cosh(right_width*(x-mz_position)), 2) (x>mz_position)
    */
    PeakShapeType::Enum type;


    /**
    	 @brief Comparator for the width.

    	 Lexicographical comparison from dimension 0 to dimension D is done.
    */
    class PositionLess
    {
    public:

      PositionLess(Int i) : dimension_(i) {}
      PositionLess() : dimension_(-1) {}
      ~PositionLess() {}

      inline bool operator () (const PeakShape& a, const PeakShape& b)
      {
        return (a.mz_position < b.mz_position);
      }

    protected:
      Int dimension_;
    };

  };
} // namespace OpenMS

#endif
