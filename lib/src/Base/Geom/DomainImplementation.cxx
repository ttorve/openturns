//                                               -*- C++ -*-
/**
 *  @brief DomainImplementation is defined as a domain of \mathbb{R}^d
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
#include "openturns/DomainImplementation.hxx"
#include "openturns/PersistentObjectFactory.hxx"
#include "openturns/Os.hxx"
#include "openturns/Exception.hxx"

BEGIN_NAMESPACE_OPENTURNS

CLASSNAMEINIT(DomainImplementation)

static const Factory<DomainImplementation> Factory_DomainImplementation;


/* Default constructor */
DomainImplementation::DomainImplementation(UnsignedInteger dimension)
  : PersistentObject()
  , dimension_(dimension)
  , volume_(0.0)
  , isAlreadyComputedVolume_(false)
{
  // Nothing to do
}

/* Clone method */
DomainImplementation * DomainImplementation::clone() const
{
  return new DomainImplementation(*this);
}

/* String converter */
String DomainImplementation::__repr__() const
{
  return OSS(true) << "class=" << GetClassName()
         << " name=" << getName()
         << " dimension=" << dimension_;

}

String DomainImplementation::__str__(const String & offset) const
{
  return OSS(false) << offset << __repr__();
}

/* Check if the given point is inside of the domain */
Bool DomainImplementation::contains(const Point & point) const
{
  throw NotYetImplementedException(HERE) << "In DomainImplementation::contains(const Point & point) const";
}

/* Check if the given point is inside of the discretization of the domain */
Bool DomainImplementation::numericallyContains(const Point & point) const
{
  return contains(point);
}

/* Check if the domain is empty, i.e if its numerical volume is zero */
Bool DomainImplementation::isEmpty() const
{
  return isNumericallyEmpty();
}

/* Check if the domain is numerically empty, i.e if its numerical volume is zero */
Bool DomainImplementation::isNumericallyEmpty() const
{
  return getNumericalVolume() <= ResourceMap::GetAsScalar("Domain-SmallVolume");
}

/* Get the volume of the domain */
Scalar DomainImplementation::getVolume() const
{
  return getNumericalVolume();
}

/* Get the numerical volume of the domain */
Scalar DomainImplementation::getNumericalVolume() const
{
  if (!isAlreadyComputedVolume_) computeVolume();
  return volume_;
}

/* Compute the volume of the mesh */
void DomainImplementation::computeVolume() const
{
  throw NotYetImplementedException(HERE);
}

/* Lower bound of the bounding box */
Point DomainImplementation::getLowerBound() const
{
  throw NotYetImplementedException(HERE) << "In DomainImplementation::getLowerBound()";
}

/* Upper bound of the bounding box */
Point DomainImplementation::getUpperBound() const
{
  throw NotYetImplementedException(HERE) << "In DomainImplementation::getUpperBound()";
}

/* Get the dimension of the domain*/
UnsignedInteger DomainImplementation::getDimension() const
{
  return dimension_;
}

/* Method save() stores the object through the StorageManager */
void DomainImplementation::save(Advocate & adv) const
{
  PersistentObject::save(adv);
  adv.saveAttribute("dimension_", dimension_);
}

/* Method load() reloads the object from the StorageManager */
void DomainImplementation::load(Advocate & adv)
{
  PersistentObject::load(adv);
  adv.loadAttribute("dimension_", dimension_);
}

END_NAMESPACE_OPENTURNS
