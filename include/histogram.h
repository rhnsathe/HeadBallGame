//
// Created by Rohan Sathe on 3/22/21.
//

#include "cinder/gl/gl.h"
#include "particle.h"

#ifndef IDEAL_GAS_HISTOGRAM_H
#define IDEAL_GAS_HISTOGRAM_H

#endif  // IDEAL_GAS_HISTOGRAM_H

#pragma once

namespace idealgas {
  class Histogram {
   public:
    /**
     * Constructor for histogram.
     * @param color
     * @param particles
     * @param num_particles
     */
    Histogram(std::vector<Particle> particles, size_t num_particles);

    /**
     * Draws the histogram for a specific colored particle.
     * @param color
     */
    void DrawHistogram(ci::Color color);

    /**
     * Returns the num_blue_ vector.
     * @return std::vector<Particle>
     */
    std::vector<Particle> GetNumBlue();

    /**
     * Returns the num_green_ vector.
     * @return std::vector<Particle>
     */
    std::vector<Particle> GetNumGreen();

    /**
     * Returns the num_orange_ vector.
     * @return std::vector<Particle>
     */
    std::vector<Particle> GetNumOrange();

   private:
    /**
     * Creates vector with blue particles.
     */
    std::vector<Particle> num_blue_;

    /**
     * Creates a vector with green particles.
     */
    std::vector<Particle> num_green_;

    /**
     * Creates a vector with orange particles.
     */
    std::vector<Particle> num_orange_;

    /**
     * Maximum blue speed, range for x-axis of histogram.
     */
    double max_blue_speed_;

    /**
     * Maximum green speed, sets range for x-axis of histogram.
     */
    double max_green_speed_;

    /**
     * Maximum orange speed, sets range for x-axis of histogram.
     */
    double max_orange_speed_;

    /**
     * Factor by which quantities are scaled.
     */
    size_t scale_factor_ = 5;

    /**
     * Add on to the width of the white box in order to start histogram.
     */
    const size_t kStartingXAddOn = 100;

    /**
     * Initial y position of first histogram.
     */
    const size_t kInitialYPosition = 10;

    /**
     * The scaling within the graph, essentially dictates
     * the width and length of the graph.
     */
    const size_t kInterYScale = 200;

    /**
     * The scaling between graphs, essentially dictates how far
     * the graphs are from each other.
     */
    const size_t kIntraYScale = 30;
  };
}
