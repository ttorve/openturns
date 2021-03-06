//                                               -*- C++ -*-
/**
 * @brief The class that implements an event domain based on a composite random vector
 *        built upon a boolean function which is described by a domain appartenance.
 *        The antecedent of the event must be a "classical" composite random
 *        vector in the context of OpenTURNS.
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

#ifndef OPENTURNS_EVENTDOMAIN_HXX
#define OPENTURNS_EVENTDOMAIN_HXX

#include "openturns/CompositeRandomVector.hxx"
#include "openturns/Domain.hxx"

BEGIN_NAMESPACE_OPENTURNS




/**
 * @class EventDomain
 *
 *
 */
class OT_API EventDomain
  : public CompositeRandomVector
{
  CLASSNAME

public:

  /** Default constructor */
  EventDomain();

  /** Constructor from RandomVector */
  EventDomain(const RandomVectorImplementation & antecedent,
              const Domain & domain);

  /** Virtual contructor */
  virtual EventDomain * clone() const;

  /** String converter */
  String __repr__() const;

  /** Dimension accessor */
  virtual UnsignedInteger getDimension() const;

  /** Domain accessor */
  Domain getDomain() const;

  /* Here is the interface that all derived class may implement */

  /** Realization accessor */
  virtual Point getRealization() const;

  /** Numerical sample accessor */
  virtual Sample getSample(const UnsignedInteger size) const;

  /** Method save() stores the object through the StorageManager */
  virtual void save(Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
  virtual void load(Advocate & adv);

private:

  /** The domain of the eventDomainImplementation */
  Domain domain_;


}; /* class EventDomain */


END_NAMESPACE_OPENTURNS

#endif /* OPENTURNS_EVENTDOMAIN_HXX */
