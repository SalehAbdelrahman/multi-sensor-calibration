/*
  multi_sensor_calibration
  Copyright (C) 2019  Intelligent Vehicles Delft University of Technology

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#pragma once
#include <Eigen/Dense>

namespace lidar_detector {

struct PassThroughFilter {
	std::string dim;
	float min;
	float max;
};

struct PlaneFilter {
	float distance_threshold;
	Eigen::Vector3f axis;
	float eps_angle;
	int max_iterations;
	bool set_negative;
	int model_type;
	bool return_projected;
};

struct CloudEdgeFilter {
	float threshold;
	float radius;
};

struct SpatialEdgeFilter {
	float search_radius;  // radius for neighbor search
	int min_neighbors;    // minimum neighbors required
	float curvature_threshold;  // threshold for edge detection based on local curvature
	float distance_threshold;   // threshold for distance-based edge detection
};

struct CircleDetection {
	float distance_threshold;
	int max_iterations;
	float min_radius;
	float max_radius;
	int cluster_iterations;
	int max_points_within_radius;
	float radius_max_points;
};

struct  Refinement {
	bool refine;
	float width;
	float height;
	float threshold_inlier;
};

struct LidarParameters {
	int number_layers;  // kept for backward compatibility, not used in solid-state mode
	bool is_solid_state;  // flag to enable solid-state processing
};

struct Configuration {
	bool visualize;
	LidarParameters lidar_parameters;
	std::vector<PassThroughFilter> pass_through_filter;
	PlaneFilter ground_floor_filter;
	PlaneFilter calibration_board_filter;
	CircleDetection circle_detection;
	CloudEdgeFilter cloud_edge_filter;  // kept for backward compatibility
	SpatialEdgeFilter spatial_edge_filter;  // new for solid-state LiDARs
	Refinement refinement;
};

}
