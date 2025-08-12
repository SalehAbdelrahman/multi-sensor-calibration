# LiDAR Detector - Solid-State and Mechanical LiDAR Support

## Overview

This library has been updated to support both **mechanical (spinning) LiDARs** (e.g., Velodyne, Ouster OS-series) and **solid-state LiDARs** (e.g., Livox, Hesai PandarQT, Ouster digital LiDARs) for calibration board detection.

## Key Differences

### Mechanical LiDARs
- **Structured Data**: Points are organized in predictable "rings" corresponding to laser channels
- **Ring-based Processing**: Uses ring topology for neighbor relationships and edge detection
- **Edge Detection**: Based on distance gaps between consecutive points in a ring

### Solid-State LiDARs  
- **Unstructured Data**: Points follow non-repeating, often random scanning patterns
- **Spatial Processing**: Uses k-d tree spatial search for neighbor relationships
- **Edge Detection**: Based on local distance variation and curvature analysis

## Configuration

### For Mechanical LiDARs
```yaml
lidar_parameters:
    number_layers: 64        # Number of laser rings (e.g., 16, 32, 64, 128)
    is_solid_state: false    # Use ring-based processing
```

### For Solid-State LiDARs
```yaml
lidar_parameters:
    number_layers: 0         # Not used for solid-state
    is_solid_state: true     # Enable spatial processing
spatial_edge_filter:
    search_radius: 0.1       # Radius for neighbor search (meters)
    min_neighbors: 5         # Minimum neighbors required for analysis
    curvature_threshold: 0.5 # Threshold for curvature-based edge detection
    distance_threshold: 0.02 # Threshold for distance variation detection
```

## Usage

### Using Pre-configured Files
1. **Mechanical LiDAR**: Use `config/config.yaml` (default configuration)
2. **Solid-State LiDAR**: Use `config/config_solid_state.yaml`

### Custom Configuration
Update the `lidar_parameters.is_solid_state` flag in your YAML configuration:

```yaml
# For mechanical LiDARs
lidar_parameters:
    is_solid_state: false

# For solid-state LiDARs  
lidar_parameters:
    is_solid_state: true
```

## Algorithm Changes

### Edge Detection Pipeline

**Mechanical LiDAR Processing:**
1. Group points by ring ID
2. Calculate distance between consecutive points in each ring
3. Identify edges based on distance gaps
4. Filter rings with insufficient points

**Solid-State LiDAR Processing:**
1. Build k-d tree for spatial neighbor search
2. For each point, find neighbors within search radius
3. Analyze local distance variation and geometry
4. Mark points with high variation as edge candidates
5. Filter based on distance thresholds

### Circle Detection
Both methods converge to the same circle detection pipeline:
1. RANSAC-based 3D circle fitting on edge points
2. Validation based on point density within circle radius
3. Iterative detection of 4 circles (calibration board pattern)

## Parameter Tuning

### Solid-State LiDAR Parameters
- **`search_radius`**: Increase for sparse point clouds, decrease for dense ones
- **`min_neighbors`**: Higher values improve robustness but may miss details
- **`distance_threshold`**: Lower values detect finer edges but increase noise
- **`curvature_threshold`**: Adjust based on calibration board circle size

### Recommended Starting Values
| LiDAR Type | search_radius | min_neighbors | distance_threshold |
|------------|---------------|---------------|-------------------|
| Livox      | 0.08-0.12     | 4-6           | 0.015-0.025       |
| Hesai QT   | 0.06-0.10     | 3-5           | 0.012-0.020       |
| Ouster SS  | 0.10-0.15     | 5-8           | 0.020-0.030       |

## Backward Compatibility

The updated code maintains full backward compatibility with existing mechanical LiDAR configurations. If `is_solid_state` is not specified, it defaults to `false` (mechanical LiDAR mode).

## Testing

To test the configuration:
1. Set appropriate parameters in YAML config
2. Run calibration detection on sample data
3. Monitor detection success rate and adjust parameters as needed
4. Use visualization mode (`visualize: true`) for debugging

## Common Issues

1. **No edge points detected**: Increase `search_radius` or decrease `distance_threshold`
2. **Too many false edges**: Decrease `search_radius` or increase `distance_threshold` 
3. **Circle fitting fails**: Adjust `min_neighbors` or circle detection parameters
4. **Performance issues**: Reduce `search_radius` or increase `min_neighbors`
