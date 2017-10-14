//                                               -*- C++ -*-
/**
 *  @brief Abstract top-level class for elliptical distributions
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
#ifndef OPENTURNS_ELLIPTICALDISTRIBUTIONIMPLEMENTATION_HXX
#define OPENTURNS_ELLIPTICALDISTRIBUTIONIMPLEMENTATION_HXX

#include "openturns/ContinuousDistribution.hxx"
#include "openturns/CorrelationMatrix.hxx"

BEGIN_NAMESPACE_OPENTURNS

/**
 * @class EllipticalDistribution
 *
 * A subclass for elliptical usual distributions.
 */
class OT_API EllipticalDistribution
  : public ContinuousDistribution
{
  CLASSNAME

public:

  // Numerical precision for computing the quantile

  /** Default constructor */
  EllipticalDistribution();

  /** Parameter constructor */
  EllipticalDistribution(const Point & mean,
                         const Point & sigma,
                         const CorrelationMatrix & R,
                         const Scalar covarianceNormalizationFactor);

  /** Virtual copy constructor */
  virtual EllipticalDistribution * clone() const;

  /** Comparison operator */
protected:
  virtual Bool equals(const DistributionImplementation & other) const;
public:

  /** String converter */
  String __repr__() const;

  /** Tell if the distribution is elliptical */
  Bool isElliptical() const;

  /** Tell if the distribution has elliptical copula */
  Bool hasEllipticalCopula() const;

  /** Get the DDF of the distribution */
  using ContinuousDistribution::computeDDF;
  Point computeDDF(const Point & point) const;

  /** Get the PDF of the distribution */
  using ContinuousDistribution::computePDF;
  Scalar computePDF(const Point & point) const;

  /** Get the PDF gradient of the distribution */
  using ContinuousDistribution::computePDFGradient;
  Point computePDFGradient(const Point & point) const;

  /** Compute the density generator of the elliptical distribution, i.e.
   *  the function phi such that the density of the distribution can
   *  be written as p(x) = phi(t(x-mu)R^{-1}(x-mu))                      */
  virtual Scalar computeDensityGenerator(const Scalar betaSquare) const;
  virtual Scalar computeLogDensityGenerator(const Scalar betaSquare) const;

  /** Compute the derivative of the density generator */
  virtual Scalar computeDensityGeneratorDerivative(const Scalar betaSquare) const;

  /** Compute the second derivative of the density generator */
  virtual Scalar computeDensityGeneratorSecondDerivative(const Scalar betaSquare) const;

  /** Compute the survival function */
  using ContinuousDistribution::computeSurvivalFunction;
  virtual Scalar computeSurvivalFunction(const Point & point) const;

  /** Get the minimum volume level set containing a given probability of the distribution */
  virtual LevelSet computeMinimumVolumeLevelSetWithThreshold(const Scalar prob, Scalar & thresholdOut) const;

  /** Mean point accessor */
  void setMean(const Point & mean);

  /** Sigma vector accessor */
  void setSigma(const Point & sigma);

  /** Sigma vector accessor */
  Point getSigma() const;

  /** Get the standard deviation of the distribution */
  Point getStandardDeviation() const;

  /** Correlation matrix accessor */
  void setCorrelation(const CorrelationMatrix & R);

  /** Correlation matrix accessor */
  CorrelationMatrix getCorrelation() const;

protected:
  /** Compute the mean of the distribution */
  void computeMean() const;

  /** Compute the covariance of the distribution */
  void computeCovariance() const;

public:
  /** Normalize the given point u_i = (x_i - mu_i) / sigma_i */
  Point normalize(const Point & x) const;

  /** Denormalize the given point x_i = mu_i + sigma_i * x_i */
  Point denormalize(const Point & u) const;

  /** Inverse correlation matrix accessor */
  SquareMatrix getInverseCorrelation() const;

  /** Cholesky factor of the correlation matrix accessor */
  TriangularMatrix getCholesky() const;

  /** Inverse of the Cholesky factor of the correlation matrix accessor */
  TriangularMatrix getInverseCholesky() const;

  /** Get the isoprobabilist transformation */
  IsoProbabilisticTransformation getIsoProbabilisticTransformation() const;

  /** Get the inverse isoprobabilist transformation */
  InverseIsoProbabilisticTransformation getInverseIsoProbabilisticTransformation() const;

  /** Get the standard distribution, i.e. a distribution of the same kind but with zero mean,
   * unit marginal standard distribution and identity correlation */
  Implementation getStandardDistribution() const;

  /** Parameters value and description accessor */
  PointWithDescriptionCollection getParametersCollection() const;
  using ContinuousDistribution::setParametersCollection;
  void setParametersCollection(const PointCollection & parametersCollection);

  /** Parameters value accessor */
  virtual Point getParameter() const;
  virtual void setParameter(const Point & parameters);

  /** Parameters description accessor */
  virtual Description getParameterDescription() const;

  /** Method save() stores the object through the StorageManager */
  void save(Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
  void load(Advocate & adv);

protected:

  /** The sigma vector of the distribution */
  mutable Point sigma_;

  /** The correlation matrix (Rij) of the distribution */
  mutable CorrelationMatrix R_;

  /** The shape matrix of the distribution = Diag(sigma_) * R_ * Diag(sigma_) */
  mutable CovarianceMatrix shape_;

  /** The inverse of the correlation matrix of the distribution */
  SymmetricMatrix inverseR_;

  /** The Cholesky factor of the shape matrix shape_ = cholesky_ * cholesky_.transpose() */
  TriangularMatrix cholesky_;

  /** The inverse Cholesky factor of the covariance matrix */
  TriangularMatrix inverseCholesky_;

  /** The normalization factor of the distribution */
  Scalar normalizationFactor_;

  /** The scaling factor of the covariance matrix covariance = covarianceScalingFactor_ * shape_*/
  Scalar covarianceScalingFactor_;

private:
  // Class used to wrap the computeRadialCDF() method for interpolation purpose
  class RadialCDFWrapper: public FunctionImplementation
  {
  public:
    RadialCDFWrapper(const EllipticalDistribution * p_distribution)
      : FunctionImplementation()
      , p_distribution_(p_distribution)
    {
      // Nothing to do
    }

    RadialCDFWrapper * clone() const
    {
      return new RadialCDFWrapper(*this);
    }

    Point operator() (const Point & point) const
    {
      return Point(1, p_distribution_->computeRadialDistributionCDF(point[0]));
    }

    UnsignedInteger getInputDimension() const
    {
      return 1;
    }

    UnsignedInteger getOutputDimension() const
    {
      return 1;
    }

    Description getInputDescription() const
    {
      return Description(1, "R");
    }

    Description getOutputDescription() const
    {
      return Description(1, "radialCDF");
    }

    String __repr__() const
    {
      OSS oss;
      oss << "RadialCDFWrapper(" << p_distribution_->__str__() << ")";
      return oss;
    }

    String __str__(const String & offset) const
    {
      OSS oss;
      oss << offset << "RadialCDFWrapper(" << p_distribution_->__str__() << ")";
      return oss;
    }

  private:
    const EllipticalDistribution * p_distribution_;
  };  // class RadialCDFWrapper

  /** Compute the value of the auxiliary attributes */
  void update();

}; /* class EllipticalDistribution */


END_NAMESPACE_OPENTURNS

#endif /* OPENTURNS_ELLIPTICALDISTRIBUTIONIMPLEMENTATION_HXX */

