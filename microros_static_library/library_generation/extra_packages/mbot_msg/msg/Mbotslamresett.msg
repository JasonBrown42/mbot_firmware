int64 utime
int32 slam_mode #mapping_only=0, action_only=1, localization_only=2, full_slam=3
string slam_map_location #only necessary when for localization-only and action_only modes
bool retain_pose #Whether to keep the pose when resetting.
