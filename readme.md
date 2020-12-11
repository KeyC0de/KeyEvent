In C++ particularly covariance allows an ovewritten virtual function's return type to be different from the base virtual function's return type, as long as its return type is inherited from the base virtual function's return type.

C++ covariance is an important feature of the language that gives rise to a well known c++ idiom known as the virtual constructor. It allows classes of an inheritance hierarchy to override a derived member function's return type with one that inherits from the base member function's return type. This function is typically known as `clone()`. Thusly allowing the creation of a perfect replica of the current class.
This is often used for constructing or perfectly forwarding pointers to objects of an inheritance hierarchy inside a container which accepts pointers to the base type.


WARNING: you can't change the return type for non-pointer and non-reference types, not even for smart pointers.

`DelayedFunc`
returns a ready-made callable with its arguments,
//			packaged in a std::unique_ptr
//			able to be inserted in any container or used for whatever purpose
//			utilizes std::function for type erasure and std::bind for argument packing

<h1 align="center">
	<a href="https://github.com/KeyC0de/ArchaicBrowser">Archaic Browser</a>
</h1>
<hr>

inspired by [this](https://stackoverflow.com/questions/30905968/how-do-i-store-a-vector-of-stdbind-without-a-specific-case-for-the-template#:~:text=Using%20std%3A%3Afunction%20seems,store%20them%20in%20a%20vector.) SO question as well as [this](https://stackoverflow.com/a/14833810/4743275) answer.


# Tagline



# Description



# Usage



# Prerequisites



# Contribute

Please submit any bugs you find through GitHub repository 'Issues' page with details describing how to replicate the problem. If you liked it or you learned something new give it a star, clone it, laugh at it, contribute to it whatever. I appreciate all of it. Enjoy.


# License

Distributed under the GNU GPL V3 License. See "GNU GPL license.txt" for more information.


# Contact

email: *nik.lazkey@gmail.com*</br>
website: *www.keyc0de.net*


another reason why we create derived Message Types is because we don't want to stick DataMessage types to our queue as that would the entire queue template itself and create complications. (Don't believe me? Try it!)

In MessageBus we use a 
	// unique_lock in `dequeue` because while you wait using a unique_lock you can relinquish
	//	control to any other threads trying to access a critical section using m_mu.
	// otherwise using a lock_guard somebody wouldn't be able to enqueue and the program
	//	would deadlock
	// wait on the condition variable while there's nothing available on the Q

# Acknowledgements



<p style="text-align: center;">
	<img src="_present/demo.jpg" />
</p>


I used Windows 8.1 x86_64, Visual Studio 2017, Modern C++17 to build the project. It should work on other platforms as well.

[C++ Virtual Construction](https://isocpp.org/wiki/faq/virtual-functions#virtual-ctors)
