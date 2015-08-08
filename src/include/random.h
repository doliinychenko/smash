/*
 *
 *    Copyright (c) 2014
 *      SMASH Team
 *
 *    GNU General Public License (GPLv3 or later)
 *
 */

#ifndef SRC_INCLUDE_RANDOM_H_
#define SRC_INCLUDE_RANDOM_H_

#include <random>

namespace Smash {

/** Namespace Random provides functions for Random Number Generation.
 */

namespace Random {

/// The random number engine used is the Mersenne Twister.
using Engine = std::mt19937_64;

/// The engine that is used commonly by all distributions.
extern /*thread_local*/ Engine engine;

/** Provides uniform random numbers on a fixed interval.
 *
 * objects of uniform_dist can be used to provide a large number of
 * random numbers in the same interval. Example:
 *
 * \code
 *   using namespace Random;
 *   double sum = 0.0;
 *   auto uniform_0_to_3 = uniform_dist(0., 3.);
 *   for (MANY_TIMES) {
 *     sum += uniform_0_to_3();
 *   }
 * \endcode
 *
 * The random number engine is completely hidden inside the object.
 */
template <typename T> class uniform_dist {
 public:
  /** creates the object and fixes the interval */
  uniform_dist(T min, T max)
    : distribution(min, max) {
  }
  /** returns a random number in the interval */
  T operator()() {
    return distribution(engine);
  }
  /** the distribution object that is being used. */
 private:
  std::uniform_real_distribution<T> distribution;
};

/** sets the seed of the random number engine. */
template <typename T> void set_seed(T &&seed) {
  engine.seed(std::forward<T>(seed));
}
/** returns a uniformly distributed random number \f$\chi \in [{\rm
 * min}, {\rm max})\f$ */
template <typename T> T uniform(T min, T max) {
  return std::uniform_real_distribution<T>(min, max)(engine);
}
/** returns a uniformly distributed random number \f$\chi \in [0,1)\f$
 */
template <typename T = double> T canonical() {
  return std::generate_canonical<T, std::numeric_limits<double>::digits>(
      engine);
}
/** returns a uniform_dist object */
template <typename T>
uniform_dist<T> make_uniform_distribution(T min, T max) {
  return uniform_dist<T>(min, max);
}
/** returns an exponentially distributed random number
 *
 * Probability for a given return value \f$\chi\f$ is \f$p(\chi) =
 * \Theta(\chi) \cdot \exp(-t)\f$
 */
template <typename T = double> T exponential(T lambda) {
  /* Work around a libstdc++ bug in std::exponential_distribution:
   * If canonical() is in [0,1) then 1.-canonical() is in (0,1] and it's safe
   * to call the log. */
  return -std::log(1.-canonical()) / lambda;
}

/** Evaluates a random number x according to an exponential distribution
 * exp(A*x), where A is assumed to be positive, and x is typically negative.
 * The result x is restricted to lie between x1 and x2 (with x2 < x <= x1). */
template <typename T = double> T expo(T A, T x1, T x2) {
  const T a1 = A * x1, a2 = A * x2;
  const T a_min = std::log(std::numeric_limits<T>::min());
#ifndef NDEBUG
  assert(A > T(0.) && T(0.) >= x1 && x1 > x2 && a1 > a_min);
#endif
  const T r1 = std::exp(a1);
  const T r2 = a2 > a_min ? std::exp(a2) : T(0.);  // prevent underflow
  return std::log(uniform(r1, r2)) / A;
}

// signum function
template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

/**
 * Draws a random number according to a power-law distribution ~ x^n.
 * \param n exponent in power law (arbitrary real number)
 * \param xMin minimum value
 * \param xMax maximum value
 * \return random number between xMin and xMax
 */
template <typename T = double> T power(T n, T xMin, T xMax) {
    const T n1 = n + 1;
    if (std::abs(n1) < 1E-3) {
      return xMin * std::pow(xMax/xMin, canonical());
    } else if (xMin > 0. && xMax > 0.) {
      return std::pow(uniform(std::pow(xMin, n1), std::pow(xMax, n1)), 1./n1);
    } else {
      return sgn(xMin) *
             std::pow(uniform(std::pow(std::abs(xMin), n1),
                              std::pow(std::abs(xMax), n1)), 1./n1);
    }
}

/**
 * Draws a random number from a non-relativistic Breit-Wigner distribution with
 * the given parameters (constant width!) inside the range [min,max].
 * \param pole Pole parameter of the Breit-Wigner function, i.e. location of the peak.
 * \param width Width parameter of the Breit-Wignr function, determining the sharpness of the peak.
 * \param min Minimum value to be returned.
 * \param max Maximum value to be returned.
 */
template <typename T = double> T breit_wigner(T pole, T width, T min, T max) {
  const T y_min = 2. * std::atan(2.*(min-pole)/width);
  const T y_max = 2. * std::atan(2.*(max-pole)/width);
  const T y = uniform(y_min, y_max);
  return pole + width/2.*std::tan(y/2.);
}

}  // namespace Random
}  // namespace Smash

#endif  // SRC_INCLUDE_RANDOM_H_
