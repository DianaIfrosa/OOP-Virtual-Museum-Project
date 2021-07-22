# Project: Virtual Museum (fictional)

Disclaimer: I do not own any of these pictures, they are for illustrative purpose only. 

In this project I have used C++ 14 (OOP) and OpenCV for creating the museum and user interface. 
 
After running, the museum can be visited by clicking 'Yes' when the first window appears. 
Then the first and last name of the client is required, as well as a category that he belongs to (adult, child, student). This step is important because the name will be stored when giving feedback, and the category is used when it comes to calculating the client's ticket price based on his category and the day of the week (each day has a specific price). After the custom price is displayed, a confirmation is needed in order to continue.  

The museum's rooms can then be visited (pictures of exhibits will pop on the screen), and the client can navigate through using buttons such as ""Go to previous room", "See again this room", "Continue tour" or "Exit". A feedback is mandatory at the end of the tour (grade between 1 and 5) and will be used to calculate the average score the museum has at that point. The Souvenir Shop can be visited at the end of the tour too and the client can see the products, their prices and a picture of them by clicking "See product" for the specific item that is desired.
 
Art or money can also be donated by clicking "Yes" when the correponding windows appear and typing again the first and last name (which will appear in  the rooms_data "database" if art is being donated), as well as specific values like the amount of money the client would like to donate (which sum up to museum's funds) or the number of a specific room. Donating art requires including a picture in the folder named "photos" with its name composed with the following rule: "photo"+number_of_exhibit+"_"+number_of_room, and the ".jpg" extension.

 Input data is stored in files such as "feedback.txt", "museum_data.in.txt" and many others. This way of storing data helps with calculating certain things and keeping track of changes over items that compose the museum. In other words, they act like a mini database for this project.


