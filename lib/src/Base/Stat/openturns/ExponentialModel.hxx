//                                               -*- C++ -*-
/**
 *  @brief This class is enables to build an exponential covariance
 *  model, a second order model's implementation
 *
 *  Copyright 2005-2017 Airbus-EDF-IMACS-Phimeca
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef OPENTURNS_EXPONENTIALMODEL_HXX
#define OPENTURNS_EXPONENTIALMODEL_HXX

#include "openturns/PersistentObject.hxx"
#include "openturns/StationaryCovarianceModel.hxx"
#include "openturns/Point.hxx"
#include "openturns/CorrelationMatrix.hxx"
#include "openturns/Mesh.hxx"

BEGIN_NAMESPACE_OPENTURNS

class RegularGrid;

/**
 * @class ExponentialModel
 */

class OT_API ExponentialModel
  : public StationaryCovarianceModel
{

  CLASSNAME

public:


  /** Constructor with spatial dimension */
  explicit ExponentialModel(const UnsignedInteger spatialDimension = 1);


  /** Standard constructor with scale and amplitude parameters parameters */
  ExponentialModel(const Point & scale,
                   const Point & amplitude);

  /** Standard constructor with scale, amplitude and spatial correlation parameters */
  ExponentialModel(const Point & scale,
                   const Point & amplitude,
                   const CorrelationMatrix & spatialCorrelation);

  /** Standard constructor with scale and spatial covariance parameters */
  ExponentialModel(const Point & scale,
                   const CovarianceMatrix & spatialCovariance);

  /** Virtual copy constructor */
  virtual ExponentialModel * clone() const;

  /** Computation of the covariance function, stationary interface */
  using StationaryCovarianceModel::computeStandardRepresentative;
  Scalar computeStandardRepresentative(const Point & tau) const;
#ifndef SWIG
  Scalar computeStandardRepresentative(const Collection<Scalar>::const_iterator & s_begin,
    const Collection<Scalar>::const_iterator & t_begin) const;
#endif

  /** Gradient */
  using StationaryCovarianceModel::partialGradient;
  Matrix partialGradient(const Point & s, const Point & t) const;

  /** Discretize the covariance function on a given TimeGrid */
  using StationaryCovarianceModel::discretize;
  CovarianceMatrix discretize(const RegularGrid & regularGrid) const;

  /** String converter */
  String __repr__() const;

  /** String converter */
  String __str__(const String & offset = "") const;

  /** Method save() stores the object through the StorageManager */
  void save(Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
  void load(Advocate & adv);

private :

} ; /* class ExponentialModel */

END_NAMESPACE_OPENTURNS

#endif /* OPENTURNS_EXPONENTIALMODEL_HXX */
