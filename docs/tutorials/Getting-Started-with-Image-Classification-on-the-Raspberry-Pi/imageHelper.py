def prepare_image_for_model(image, requiredWidth, requiredHeight, reorderToRGB = False):
    """ Prepare an image for use with a model. Typically, this involves:
        - Resize and center crop to the required width and height while preserving the image's aspect ratio.
          Simple resize may result in a stretched or squashed image which will affect the model's ability
          to classify images.
        - OpenCV gives the image in BGR order, so we may need to re-order the channels to RGB.
        - Convert the OpenCV result to a std::vector<float> for use with ELL model
    """
    if image.shape[0] > image.shape[1]:  # Tall (more rows than cols)
        rowStart = int((image.shape[0] - image.shape[1]) / 2)
        rowEnd = rowStart + image.shape[1]
        colStart = 0
        colEnd = image.shape[1]
    else:  # Wide (more cols than rows)
        rowStart = 0
        rowEnd = image.shape[0]
        colStart = int((image.shape[1] - image.shape[0]) / 2)
        colEnd = colStart + image.shape[0]
    # Center crop the image maintaining aspect ratio
    cropped = image[rowStart:rowEnd, colStart:colEnd]
    # Resize to model's requirements
    resized = cv2.resize(cropped, (requiredHeight, requiredWidth))
    # Re-order if needed
    if not reorderToRGB:
        resized = cv2.cvtColor(resized, cv2.COLOR_BGR2RGB)
    # Return as a vector of floats
    result = resized.astype(np.float).ravel()
    return result
