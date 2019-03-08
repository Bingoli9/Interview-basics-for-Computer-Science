## vector init

#### vector\<int\> list

vector is empty and size is 0, indicating that there are no elements in the container, and capacity also returns 0, meaning that no memory space has been allocated.This initialization method is suitable for situations where the number of elements is unknown and needs to be added dynamically in the program.

#### vector\<int\> ilist2(ilist);

#### vector\<int\> ilist = {1,2,3.0,4,5,6,7};

#### vector\<int\> ilist {1,2,3.0,4,5,6,7}

vector\<int\> ilist3(ilist.begin()+2,ilist.end()-1);

vector\<int\> ilist3(ilist.begin()+2,ilist.end()-1)







 vector\<int\> ilist3(ilist.begin()+2,ilist.end()-1)

#### vector\<int\> ilist4(7)

Default initialization, ilist4 will contain seven elements, each element for the default value initialization, for int, that is assigned to 0, so ilist4 is initialized to contain seven 0.This initialization is used when the initial number of elements is predictable and the values of the elements need to be retrieved dynamically.

#### vector\<int\> ilist5(7,3)

Ilist5 is initialized to an int vector containing seven values of 3

