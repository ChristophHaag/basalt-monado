/**
BSD 3-Clause License

This file is part of the Basalt project.
https://gitlab.com/VladyslavUsenko/basalt.git

Copyright (c) 2019, Vladyslav Usenko and Nikolaus Demmel.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of the copyright holder nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#pragma once

#include <string>
#include <vector>

namespace basalt {

enum class LinearizationType { ABS_QR, ABS_SC, REL_SC };
enum class MatchingGuessType { SAME_PIXEL, REPROJ_FIX_DEPTH, REPROJ_AVG_DEPTH };
enum class KeyframeMargCriteria { KF_MARG_DEFAULT, KF_MARG_FORWARD_VECTOR };

struct VioConfig {
  VioConfig();
  void load(const std::string& filename);
  void save(const std::string& filename);

  std::string optical_flow_type;
  int optical_flow_detection_grid_size;
  int optical_flow_detection_num_points_cell;
  int optical_flow_detection_min_threshold;
  int optical_flow_detection_max_threshold;
  bool optical_flow_detection_nonoverlap;
  float optical_flow_max_recovered_dist2;
  int optical_flow_pattern;
  int optical_flow_max_iterations;
  int optical_flow_levels;
  float optical_flow_epipolar_error;
  int optical_flow_skip_frames;
  MatchingGuessType optical_flow_matching_guess_type;
  float optical_flow_matching_default_depth;
  float optical_flow_image_safe_radius;                    // Use to mask black corners in cameras
  bool optical_flow_recall_enable;                         // Enable feature/landmark recall
  bool optical_flow_recall_all_cams;                       // Recall in all cameras, not just cam0
  bool optical_flow_recall_num_points_cell;                // Respect gridcell feature limit
  bool optical_flow_recall_over_tracking;                  // Always perform recall, even on already tracked features
  bool optical_flow_recall_update_patch_viewpoint;         // Update feature patch when succesfully recalled
  float optical_flow_recall_max_patch_dist;                // Maximum distance in % of width to accept a recall, or 0
  std::vector<float> optical_flow_recall_max_patch_norms;  // Maximum patch residual norm to accept a recall

  LinearizationType vio_linearization_type;
  bool vio_sqrt_marg;

  int vio_max_states;
  int vio_max_kfs;
  int vio_min_frames_after_kf;
  float vio_new_kf_keypoints_thresh;
  bool vio_debug;
  bool vio_extended_logging;

  //  double vio_outlier_threshold;
  //  int vio_filter_iteration;
  int vio_max_iterations;

  double vio_obs_std_dev;
  double vio_obs_huber_thresh;
  double vio_min_triangulation_dist;

  bool vio_enforce_realtime;

  bool vio_use_lm;
  double vio_lm_lambda_initial;
  double vio_lm_lambda_min;
  double vio_lm_lambda_max;

  bool vio_scale_jacobian;

  double vio_init_pose_weight;
  double vio_init_ba_weight;
  double vio_init_bg_weight;

  bool vio_marg_lost_landmarks;
  bool vio_fix_long_term_keyframes;
  double vio_kf_marg_feature_ratio;
  KeyframeMargCriteria vio_kf_marg_criteria;  // Keyframe removal criteria

  double mapper_obs_std_dev;
  double mapper_obs_huber_thresh;
  int mapper_detection_num_points;
  double mapper_num_frames_to_match;
  double mapper_frames_to_match_threshold;
  double mapper_min_matches;
  double mapper_ransac_threshold;
  double mapper_min_track_length;
  double mapper_max_hamming_distance;
  double mapper_second_best_test_ratio;
  int mapper_bow_num_bits;
  double mapper_min_triangulation_dist;
  bool mapper_no_factor_weights;
  bool mapper_use_factors;

  bool mapper_use_lm;
  double mapper_lm_lambda_min;
  double mapper_lm_lambda_max;
};

}  // namespace basalt
