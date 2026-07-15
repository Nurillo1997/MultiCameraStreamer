# MultiCameraStreamer

A simple multi-camera streaming application written in C using GStreamer.

The application creates an independent GStreamer pipeline for each camera and publishes video streams over RTSP using MediaMTX.

## Features

- Multiple independent GStreamer pipelines
- MP4 files as virtual camera sources
- RTSP camera source support
- H.264 encoding
- RTSP streaming with MediaMTX
- Automatic MP4 looping
- Graceful shutdown

## Project Structure

```text
MultiCameraStreamer/
|
├── CMakeLists.txt
├── README.md
|
├── config/
│   ├── streams.json
│   └── mediamtx.yml
|
├── videos/
|
├── include/
│   ├── application.h
│   ├── camera.h
│   ├── camera_pipeline.h
│   ├── config_manager.h
│   └── pipeline_manager.h
|
└── src/
    ├── main.c
    ├── application.c
    ├── camera.c
    ├── camera_pipeline.c
    ├── config_manager.c
    └── pipeline_manager.c
```

## Workflow

Each camera runs in its own independent GStreamer pipeline.

```text
MP4 File / RTSP Camera
        ↓
    GStreamer
        ↓
   Video Decode
        ↓
   H.264 Encode
        ↓
   RTSP Publish
        ↓
     MediaMTX
        ↓
    RTSP Client

## Configuration

Camera streams are configured in:

```text
config/streams.json
```

Example:

```json
{
    "cameras": [
        {
            "id": 1,
            "name": "Camera 1",
            "source": "videos/camera1.mp4",
            "type": "file",
            "rtsp_url": "rtsp://localhost:8554/camera1"
        },
        {
            "id": 2,
            "name": "Camera 2",
            "source": "videos/camera2.mp4",
            "type": "file",
            "rtsp_url": "rtsp://localhost:8554/camera2"
        }
    ]
}
```

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Run

Start MediaMTX:

```bash
mediamtx config/mediamtx.yml
```

Then run the application:

```bash
./build/MultiCameraStreamer
```

Default RTSP streams:

```text
rtsp://localhost:8554/camera1
rtsp://localhost:8554/camera2
```

Stop the application with `Ctrl+C`.