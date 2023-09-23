# SlasherFullCppDemo
An Unreal Engine 5 Slasher game trial with full C++ code. My blueprint usage is minimal.


- A C++ Demo Slasher game. I used enhanced input C++ side input binding. Currently my important events are not exposed to blueprints. However, in the future I am going to expose the important events ( such as hit events ) to blueprints via interfaces. This project is still in its early phases.

What did I do so far in C++ 
- I bound my inputs with enhanced input using C++. I used all kinds of input types ( such as boolean, float, Vector2D and FVector input types )
- I created my own animinstance class and exposed necessary variables to animation blueprint.
- I added multiple animgraphs to my main anim graph.
- I peered animmontage notifies with my animinstance or character C++ based blueprint exposed functions, ensured clean and precise coding.
- Created multiple global character enum states.
- Currently creating C++ based widgets.
- Created the following Item inheritance hierarchy ( Its design is not complete )

![image](https://github.com/KaanSamet/SlasherFullCppDemo/assets/94367236/0d7a07f4-6be9-49e1-adae-1ea5da984418)

What did I do so far asset-wise

- I have found and imported various free assets in order to make the game interesting.
- I mainly used quixel and mixamo.



