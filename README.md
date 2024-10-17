GraphIt aims to implement a number of graph drawing algorithms in C++. Currently the focus is on spectral graph drawing methods, but there will be implementations of other techniques as well (such as force based drawings).

These papers relate to the currently implemented algorithms:

Drawing Graphs By Eigenvectors: Theory and Practice - Y. Koren
  
An r-dimensional quadratic placement algoritm - K.M. Hall

The Eigen and Spectra libraries are essential for matrix manipulations and spectral calculations, and SFML is used to render the results.

Below is shown some sample output:

![Screenshot from 2024-10-17 00-10-52-0](https://github.com/user-attachments/assets/90b98079-0ecd-4425-96e7-3803f8e51b6c)
![Screenshot from 2024-10-17 00-10-52-1](https://github.com/user-attachments/assets/d271d3ba-64c7-4761-94ed-e948a8fe6807)
![Screenshot from 2024-10-17 00-10-52-2](https://github.com/user-attachments/assets/8f69dd3b-711e-430d-b1b5-400fee87546e)
![Screenshot from 2024-10-17 00-10-52-5](https://github.com/user-attachments/assets/b3c2f234-887a-4c42-ae43-1fe181d8c004)
![Screenshot from 2024-10-17 00-10-52-6](https://github.com/user-attachments/assets/d6198f0b-caf7-46d1-b271-513ae70cd15a)
![Screenshot from 2024-10-17 00-10-52-7](https://github.com/user-attachments/assets/83313a77-605c-426a-80bd-ac953904ff30)

The follwing output was produced using a modified version of the algorithm which produced the above images. In this new case the graphs are embedded into an appropriately chosen vector space before calculations are run. This allows the algorithm to deal with much larger graphs in finite time.

![Screenshot from 2024-10-17 00-10-52-8](https://github.com/user-attachments/assets/77483bb9-2662-4332-9c5e-c1ce02783908)
![Screenshot from 2024-10-17 00-10-52-9](https://github.com/user-attachments/assets/60806faa-3767-496f-8d93-af85465ea692)
