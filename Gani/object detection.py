import cv2

# Read image
image = cv2.imread("C:/Users/OBULESU PENDEM/Gani/rgb.png")

# Check image
if image is None:
    print("Image not found")
    exit()

# Resize image
image = cv2.resize(image, (400, 300))

# Display original image
cv2.imshow("Original Image", image)

# Convert to grayscale
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

cv2.imshow("Grayscale Image", gray)

# Thresholding
ret, thresh = cv2.threshold(
    gray,
    150,
    255,
    cv2.THRESH_BINARY
)

cv2.imshow("Threshold", thresh)

# Find contours
contours, _ = cv2.findContours(
    thresh,
    cv2.RETR_EXTERNAL,
    cv2.CHAIN_APPROX_SIMPLE
)

# Draw contours
contour_image = image.copy()

cv2.drawContours(
    contour_image,
    contours,
    -1,
    (0, 255, 0),
    2
)

cv2.imshow("Contours", contour_image)

# Copy image for bounding box
bounding_image = image.copy()

# Select largest contour as phone
if contours:

    phone = max(contours, key=cv2.contourArea)

    if cv2.contourArea(phone) > 100:

        x, y, w, h = cv2.boundingRect(phone)

        # Draw bounding box
        cv2.rectangle(
            bounding_image,
            (x, y),
            (x + w, y + h),
            (0, 255, 0),
            2
        )

        # Add label
        cv2.putText(
            bounding_image,
            "PHONE",
            (x, max(20, y - 5)),
            cv2.FONT_HERSHEY_SIMPLEX,
            0.6,
            (0, 255, 0),
            2
        )

# Display result
cv2.imshow("Phone Bounding Box", bounding_image)

cv2.waitKey(0)
cv2.destroyAllWindows()
