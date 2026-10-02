import cv2

# Read image
image = cv2.imread(r"C:\Users\OBULESU PENDEM\Gani\rgb.png")

# Check image
if image is None:
    print("Image not found")
    exit()

print("Image loaded successfully")

# Resize image
image = cv2.resize(image, (400, 300))

# Display original image
cv2.imshow("Original Image", image)

# Convert to grayscale
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

cv2.imshow("Gray Image", gray)

cv2.waitKey(0)
cv2.destroyAllWindows()