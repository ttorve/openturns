//                                               -*- C++ -*-
/**
 *  @brief Implementation for metamodel algorithms
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
#ifndef OPENTURNS_METAMODELALGORITHM_HXX
#define OPENTURNS_METAMODELALGORITHM_HXX

#include "openturns/Point.hxx"
#include "openturns/Sample.hxx"
#include "openturns/Function.hxx"
#include "openturns/Distribution.hxx"
#include "openturns/MetaModelResult.hxx"

BEGIN_NAMESPACE_OPENTURNS



/**
 * @class MetaModelAlgorithm
 *
 */

class OT_API MetaModelAlgorithm
  : public PersistentObject
{
  CLASSNAME
public:


  /** Default constructor */
  MetaModelAlgorithm();

  /** Constructor with parameters */
  MetaModelAlgorithm(const Distribution & distribution,
                     const Function & model);

  /** Virtual constructor */
  virtual MetaModelAlgorithm * clone() const;

  /** String converter */
  virtual String __repr__() const;

  /** Distribution accessor */
  void setDistribution(const Distribution & distribution);
  Distribution getDistribution() const;

  /** Response surface computation */
  virtual void run();

  /** Sample accessors */
  virtual Sample getInputSample() const;
  virtual Sample getOutputSample() const;

  /** Method save() stores the object through the StorageManager */
  virtual void save(Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
  virtual void load(Advocate & adv);

protected:

  /** The input vector distribution */
  Distribution distribution_;

  /** The model */
  Function model_;


private:


}; /* class MetaModelAlgorithm */

END_NAMESPACE_OPENTURNS

#endif /* OPENTURNS_METAMODELALGORITHM_HXX */
