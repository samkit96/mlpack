/***
 * @file mahalanobis_dstance.h
 * @author Ryan Curtin
 *
 * The Mahalanobis distance.
 */
#ifndef __MLPACK_CORE_KERNELS_MAHALANOBIS_DISTANCE_H
#define __MLPACK_CORE_KERNELS_MAHALANOBIS_DISTANCE_H

#include <armadillo>

namespace mlpack {
namespace kernel {

/**
 * The Mahalanobis distance, which is essentially a stretched Euclidean
 * distance.  Given a square covariance matrix @f$ Q @f$ of size @f$ d @f$ x
 * @f$ d @f$, where @f$ d @f$ is the dimensionality of the points it will be
 * evaluating, and given two vectors @f$ x @f$ and @f$ y @f$ also of
 * dimensionality @f$ d @f$,
 *
 * @f[
 * d(x, y) = \sqrt{(x - y)^T Q (x - y)}
 * @f]
 *
 * where Q is the covariance matrix.
 *
 * Because each evaluation multiplies (x_1 - x_2) by the covariance matrix, it
 * may be much quicker to use an LMetric and simply stretch the actual dataset
 * itself before performing any evaluations.  However, this class is provided
 * for convenience.
 *
 * Similar to the LMetric class, this offers a template parameter t_take_root
 * which, when set to false, will instead evaluate the distance
 *
 * @f[
 * d(x, y) = (x - y)^T Q (x - y)
 * @f]
 *
 * which is faster to evaluate.
 *
 * @tparam t_take_root If true, takes the root of the output.  It is slightly
 *   faster to leave this at the default of false.
 */
template<bool t_take_root = false>
class MahalanobisDistance {
 public:
  /**
   * Initialize the Mahalanobis distance with the empty matrix as covariance.
   * Because we don't actually know the size of the vectors we will be using, we
   * delay creation of the covariance matrix until evaluation.
   */
  MahalanobisDistance() : covariance_(0, 0) { }

  /**
   * Initialize the Mahalanobis distance with the given covariance matrix.  The
   * given covariance matrix will be copied (this is not optimal).
   *
   * @param covariance The covariance matrix to use for this distance.
   */
  MahalanobisDistance(const arma::mat& covariance) : covariance_(covariance) { }

  /**
   * Evaluate the distance between the two given points using this Mahalanobis
   * distance.
   *
   * @param a First vector.
   * @param b Second vector.
   */
  double Evaluate(const arma::vec& a, const arma::vec& b);

  /**
   * Access the covariance matrix.
   *
   * @return Constant reference to the covariance matrix.
   */
  const arma::mat& GetCovariance() const { return covariance_; }

  /**
   * Modify the covariance matrix.
   *
   * @return Reference to the covariance matrix.
   */
  arma::mat& GetCovariance() { return covariance_; }

 private:
  //! The covariance matrix associated with this distance.
  arma::mat covariance_;
};

}; // namespace kernel
}; // namespace mlpack

#include "mahalanobis_distance_impl.hpp"

#endif