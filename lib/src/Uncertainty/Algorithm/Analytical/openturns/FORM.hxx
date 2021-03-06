//                                               -*- C++ -*-
/**
 *  @brief FORM implements the First Order Reliability Method
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
#ifndef OPENTURNS_FORM_HXX
#define OPENTURNS_FORM_HXX

#include "openturns/Analytical.hxx"
#include "openturns/FORMResult.hxx"

BEGIN_NAMESPACE_OPENTURNS



/**
 * @class FORM
 * FORM implements the First Order Reliability Method
 * and compute the results of such kind of analyses
 */

class OT_API FORM
  : public Analytical
{

  CLASSNAME
public:


  /** Default constructor */
  FORM();

  /** Constructor with parameters */
  FORM(const OptimizationAlgorithm & nearestPointAlgorithm,
       const Event & event,
       const Point & physicalStartingPoint);


  /** Virtual constructor */
  virtual FORM * clone() const;

  /** Result accessor */
  FORMResult getResult() const;

  /** Result accessor */
  void setResult(const FORMResult & formResult);

  /** String converter */
  String __repr__() const;

  /** Function that computes the design point by re-using the Analytical::run() and creates a FORM::Result */
  void run();

  /** Method save() stores the object through the StorageManager */
  void save(Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
  void load(Advocate & adv);

private:

  FORMResult formResult_;
} ; /* class FORM */

END_NAMESPACE_OPENTURNS

#endif /* OPENTURNS_FORM_HXX */



