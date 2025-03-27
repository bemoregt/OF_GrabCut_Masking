# OF_GrabCut_Masking

OpenFrameworks implementation of GrabCut algorithm for interactive image segmentation.

## Description

This project implements an interactive image segmentation tool using OpenCV's GrabCut algorithm in OpenFrameworks. Users can draw a bounding box around an object, and the algorithm will automatically separate the foreground from the background.

## Features

- Interactive bounding box selection
- Real-time visualization of segmentation results
- Semi-transparent overlay of segmented area
- Drag and drop image loading
- Automatic saving of segmentation masks

## Demo Images

### Segmenting a Red Apple
![Demo 1 - Apple Segmentation](https://raw.githubusercontent.com/bemoregt/OF_GrabCut_Masking/main/demo_images/%20demo1.png)

### Segmenting a Spray Bottle
![Demo 2 - Spray Bottle Segmentation](https://raw.githubusercontent.com/bemoregt/OF_GrabCut_Masking/main/demo_images/demo2.jpg)

### Segmenting a Pear
![Demo 3 - Pear Segmentation](https://raw.githubusercontent.com/bemoregt/OF_GrabCut_Masking/main/demo_images/demo3.jpg)

## Dependencies

- OpenFrameworks 0.11.0+
- ofxCv addon

## How to Use

1. Run the application
2. Drag and drop an image file into the window
3. Click and drag to create a bounding box around the object you want to segment
4. Release the mouse button to perform segmentation
5. The result will be displayed as an overlay and saved as "seg_mask.jpg"

## Implementation Details

The application uses OpenCV's GrabCut algorithm with 9 iterations for segmentation. The segmented result is visualized as a semi-transparent overlay on top of the original image, and the final mask is saved to disk.

## License

MIT

## Author

bemoregt
