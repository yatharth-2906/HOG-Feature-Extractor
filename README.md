# HOG-Feature-Extractor

HOG is a feature descriptor for object recognition, including face recognition for humans.It takes count of all gradient orientation occurrences by using image segmentation (Dalaland Triggs, 2005). The shape and appearance of a local object in an image can beaccounted for by understanding the edge patterns in it. Image is segmented intoconnected regions called cells, and a histogram is made from the pixels within each cell. Multiple cells have uniformity in their space form a dense grid. HOG is calculated byusing this dense grid that uses the overlapping of segmented contrast normalisation forimprovement in accuracy (Deniz et al., 2011). HOG features are directly proportional to the image size.

![HOG_1](https://user-images.githubusercontent.com/97800277/204135024-54b83b77-2910-4696-8ca5-bef12f5f2980.jpg)

# Applications Of HOG

HOG descriptors are mainly used to describe the structural shape and appearance of an object in an image, making them excellent descriptors for object classification. However, since HOG captures local intensity gradients and edge directions, it also makes for a good texture descriptor. The HOG descriptor returns a real-valued feature vector which is mainly used in the application of object detection like facial recognition.

![HOG_2](https://user-images.githubusercontent.com/97800277/204150919-cd4398a5-e550-45d0-b0a3-c7af1685156a.jpg)

# Steps to Generate HOG Fearures

- Input Image
- Gradient Computations
- Magnitude Computations
- Histogram Generation

# Screenshoot

![HOG_3](https://user-images.githubusercontent.com/97800277/204150993-b692055d-5a72-41f3-bde6-bf338c72c745.png)
