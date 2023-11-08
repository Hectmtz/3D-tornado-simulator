# 3D-tornado-simulator
This project aims to simulate the behavior of a tornado and the interaction of objects of different sizes with it in a three-dimensional manner.

### 1. Introduction

This project aims to simulate the behavior of a tornado and the interaction of objects of different sizes with it, using transformations such as translation, scaling, and rotation. Bézier curves will also be implemented within the simulation.

One of the objectives of this project is to understand how a tornado behaves and to explore the interactions it has with its environment. Understanding these situations provides us with a clearer insight into this phenomenon and allows us to take necessary precautions when dealing with it. Additionally, this simulation can be used for educational purposes in relevant subjects. However, the primary goal of this project is the implementation of computer graphics methods.

### 2. Body

We will begin by explaining what an OBJ and PLY format object is.

A PLY format object is a file that contains information about a three-dimensional model, and thus, it includes attributes in the 'x,' 'y,' and 'z' coordinate axes. The PLY file is divided into two parts. The first part, located at the top, contains the number of vertices and faces of our object. The second part contains the numerical information of each vertex and face, delimited only by spaces.

Moving on to the OBJ format object, similar to PLY objects, it serves as a storage file for three-dimensional model information. However, this file extension has different structural characteristics. Unlike the previous format, OBJ files do not specify the number of vertices and faces. Instead, each line of information begins with a letter in its first character, indicating whether it is a vertex or a face. It is worth noting that while vertices are separated only by a space, faces have diagonals among their characteristics, allowing for more object customization possibilities.

Once the explanation of the formats used is completed, we will proceed to present the class diagram and the function of each class. We will start by explaining the 'models' class, which is the parent class from which two other classes inherit: the 'Obj' class and the 'Ply' class. The 'models' class implements all the methods shared by each of the inherited classes, such as methods for calculating Bézier or Hermite curves, and the corresponding getters and setters, as well as abstract methods that allow us to load our models into any class where they are needed. Each of the two classes that inherit from this class has their respective overwrites of the abstract methods with their correct implementation for loading OBJ and PLY format files. [Fig. 1].

![1](https://github.com/Hectmtz/3D-tornado-simulator/assets/145248331/cb971808-4fc4-4cd0-a677-eb564f6448f3)\
Figure 1: OBJ, PLY and models classes.

The next class to be explained is the 'Scene' class [Fig. 2]. This class, as it is, already implements all the other classes in the project and directly contains objects of two other classes, namely, 'Box' and 'Tornado.' It practically implements all the methods of the project as it is responsible for drawing each of the models on the screen.

![2](https://github.com/Hectmtz/3D-tornado-simulator/assets/145248331/32ddc0e1-191e-41bf-b98c-a898134533f8)\
Figure 2: Scene Class containing all the models to be rendered

Finally, the following classes will be explained [Fig. 3]. These classes are used throughout the project as they are primarily responsible for loading objects and obtaining their data for rendering. The 'Transform' class implements all the methods used to perform transformations on our objects. Once all the classes have been explained, it is important to highlight that there are relationships between them that are not visible graphically due to space and organization constraints in this work. This includes the relationship of the 'vertex,' 'edge,' and 'face' classes with the 'obj' and 'ply' classes, and so on.

The tests conducted during the implementation of the project involved analyzing the behavior of tornadoes and their interactions with other objects (Edward M Brooks, "The tornado cyclone," Weatherwise 2, no. 2 (1949): 32-33). Through calculations, we aimed to simulate how each of our implementations could be as close to reality as possible.

Below, the models used for our tornado [Fig. 4], our box [Fig. 6], and our ball [Fig. 5] are presented.

![tornado](https://github.com/Hectmtz/3D-tornado-simulator/assets/145248331/1b21f96a-4fe1-402a-847e-e70bcd37b425)\
Figure 4: Tornado model.

![ball](https://github.com/Hectmtz/3D-tornado-simulator/assets/145248331/d9c6445c-982f-468b-ac63-b51a781666ea)</br>
Figure 5: ball model.

![box](https://github.com/Hectmtz/3D-tornado-simulator/assets/145248331/80c405fd-b624-4af9-a69a-71bbbcac231c)</br>
Figure 6: Box model.

One of the significant challenges during the implementation of our simulation program was dynamically calculating Bézier curves when an object rotating around our tornado had to be ejected in a specific direction. This was achieved optimally when the tornado was located within the octants with negative z values in our coordinate system. However, it exhibited altered behavior when the tornado was within the octants with positive z values.

### 3. Bibliography
Brooks, Edward M. "The Tornado Cyclone." Weatherwise 2, no. 2 (1949): 32-33.
