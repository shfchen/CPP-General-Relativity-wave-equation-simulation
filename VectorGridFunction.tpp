#include "VectorGridFunction.h"

//Constructor that initializes to a specific value. If inner vector size and 
//array size are fixed, outer vector size may be zero and additional 
//GridFunctions may be appended later.
template <class T>
VectorGridFunction<T>::VectorGridFunction(int outerVecSize, 
                                          int innerVecSize, int arraySize, 
                                          T initvalue):
  VGFvectorDim(outerVecSize), GFvectorDim(innerVecSize), GFarrayDim(arraySize)
{
  if(outerVecSize<0) {
    cout << "Negative Vector dimensions at VectorGridFunction constructor." << endl;
  }
  
  for(int i=0; i<outerVecSize; i++) {
    GridFunction<T> temp(innerVecSize,arraySize,initvalue);
    data.push_back(temp);
  }
}

//Uninitialized constructor. Same property for outerVecSize=0 as above.
template <class T>
VectorGridFunction<T>::VectorGridFunction(int outerVecSize, 
                                          int innerVecSize, int arraySize):
  VGFvectorDim(outerVecSize), GFvectorDim(innerVecSize), GFarrayDim(arraySize)
{
  if(outerVecSize<0){
    cout << "Negative Vector dimensions at VectorGridFunction constructor." << endl;
  }
  
  for(int i = 0; i < outerVecSize; i++){
    GridFunction<T> temp(innerVecSize,arraySize);
    data.push_back(temp);
  }
}

//Set the value of a specific point. 
template <class T>
void VectorGridFunction<T>::set(int VGFvcoord, int GFvcoord, int GFacoord,
                                T value)
{
  if((0 > VGFvcoord) || (VGFvcoord >= VGFvectorDim)){
    cout << "Vector index out of range in set" << endl;
  }
  
  data.at(VGFvcoord).set(GFvcoord,GFacoord,value);
}

//Set an outer vector coordinate to a grid function.
template <class T>
void VectorGridFunction<T>::set(int VGFcoord, GridFunction<T> gf)
{
  if((0 > VGFcoord) || (VGFcoord >= VGFvectorDim)){
    cout << "Vector index out of range in set" << endl;
  }

  data.at(VGFcoord)=gf;
}

//Set an outer and inner vector coordinate to an vector.
template <class T>
void VectorGridFunction<T>::set(int VGFcoord, int GFcoord, std::vector<T> arr)
{

  if((0 > VGFcoord)||(VGFcoord >= VGFvectorDim)){
    cout << "Vector index out of range in set" << endl;
  }

  data.at(VGFcoord).set(GFcoord,arr);

}

//Set an inner vector coordinate and an array coordinate to a vector of values.
template <class T>
void VectorGridFunction<T>::setVector(int GFcoord, int GFacoord, vector<T> vec)
{
  if((GFcoord < 0) || (GFacoord < 0) || (GFacoord > GFarrayDim)){
    cout << "Coordinates in setVector out of range." << endl;
  }
  for(int i = 0; i < VGFvectorDim; i++){
    data.at(i).set(GFcoord,GFacoord,vec[i]);
  }
}

//Get the value of a specific point.
template <class T>
T VectorGridFunction<T>::get(int VGFvcoord, int GFvcoord, int GFacoord)
{
  if((0 > VGFvcoord) || (VGFvcoord >= VGFvectorDim)){
    cout << "Vector index out of range in get" << endl;
  }
  return data.at(VGFvcoord).get(GFvcoord,GFacoord);
}

//Get an array from an inner and outer vector coordinate.
template <class T>
vector<T> VectorGridFunction<T>::get(int VGFvcoord,int GFvcoord)
{
  if((0 > VGFvcoord) || (VGFvcoord >= VGFvectorDim)){
    cout << "Vector index out of range in get" << endl;
  }
  return data.at(VGFvcoord).get(GFvcoord);
}
 

//Get a GridFunction from an outer vector coordinate.
template <class T>
GridFunction<T> VectorGridFunction<T>::get(int VGFvcoord)
{
  if((0 > VGFvcoord) || (VGFvcoord >= VGFvectorDim)){
    cout << "Vector index out of range in get" << endl;
  }
  return data.at(VGFvcoord);
}


//Append a GridFunction to the end of the VectorGridFunction.
template <class T>
void VectorGridFunction<T>::append(GridFunction<T> gf)
{
  VGFvectorDim++;
  data.push_back(gf);
}

//May be obsolete.
template <class T>
void VectorGridFunction<T>::save(string filename)
{
  ofstream fs;
  fs.open(filename);
   
  for(int j=0; j<GFvectorDim; j++){
    for(int k = 0; k<GFarrayDim; k++){
      for(int i=0; i<VGFvectorDim; i++){
        fs << data.at(i).get(j,k) << " ";
      }
      fs << endl;
    }
  }
  fs.close();
}


//Get a vector from an inner vector coordinate and an array coordinate.
template <class T>              
vector<T> VectorGridFunction<T>::getVector(int GFvcoord, int GFacoord)
{
  if((GFvcoord < 0) || (GFvcoord >= GFvectorDim) || (GFacoord < 0)
     || (GFacoord > GFarrayDim)) {
    cout << "Get indices out of range." << endl;
  }
  
  vector<T> outputvec;
  for(int i = 0; i < VGFvectorDim; i++) {
    outputvec.push_back(get(i, GFvcoord, GFacoord));
  }
  return outputvec;
}
    
//Get an vector from an inner vector coordinate and an array coordinate, 
//ranging from outer vector index vmin to vmax.
template <class T>
vector<T> VectorGridFunction<T>::getVectorRegion(int GFvcoord, 
                                                     int GFacoord, int vmin, 
                                                     int vmax)

{
  if((GFvcoord < 0) || (GFvcoord >= GFvectorDim) || (GFacoord < 0)
     || (GFacoord > GFarrayDim)) {
    cout << "Get indices out of range." << endl;
  }
  
  if((vmax > VGFvectorDim) || (vmin < 0)) {
    cout << "Get max or min vector indices out of range" << endl;
  }

  vector<T> outputvec(vmax - vmin + 1);
  for(int i = vmin; i <= vmax; i++){
    outputvec[i - vmin] =get(i, GFvcoord, GFacoord);
  }
  return outputvec;
}

/*//Get an Array2D containing the values of the VGF at an inner vector
//coordinate, with the outer vector values running along the rows
//and the array values running along the columns. Begins selecting
//outer vector values at startvec and ends at stopvec.
template <class T>
Array2D<T> VectorGridFunction<T>::getVectorNodeArray2D(int GFcoord,
                                                       int startvec, 
                                                       int stopvec)
{
  if((GFcoord < 0) || (GFcoord > GFvectorDim)) {
    cout << "Get indices out of range" << endl;
  }

  if((startvec < 0) || (stopvec >= VGFvectorDim)) {
    cout << "Endpoints of vector requested are out of range" << endl;
  }
  
  Array2D<T> output(GFarrayDim, stopvec - startvec + 1);
  for(int i = startvec; i <= stopvec; i++){
    for(int j = 0; j < GFarrayDim; j++){
      output[j][i - startvec]=get(i, GFcoord, j);
    }
  }
  return output;
}*/

//-----------------------------
//not in class

//Addition operator for VectorGridFunctions.
template <typename T>
VectorGridFunction<T> operator+(VectorGridFunction<T> vgf1, 
                                VectorGridFunction<T> vgf2)
{
  if(vgf1.VGFdim() != vgf2.VGFdim()){
    cout << "Vector dimension mismatch in + operation" << endl;
  }
  VectorGridFunction<T> vgfsum(0, vgf1.GFvecDim(), vgf1.GFarrDim());
  for(int i = 0; i < vgf1.VGFdim(); i++){
    vgfsum.append(vgf1.get(i) + vgf2.get(i));
  }
  return vgfsum;
}

//Scalar multiplication operator for VectorGridFunctions.
template <typename T>
VectorGridFunction<T> operator*(T A, VectorGridFunction<T> vgf)
//for easy multiplication in rk4 routine
{
  VectorGridFunction<T> vgfprod(0, vgf.GFvecDim(), vgf.GFarrDim());
  for(int i = 0; i < vgf.VGFdim(); i++){
    vgfprod.append(A * vgf.get(i));
  }
  return vgfprod;
}


//Scalar multiplication operator for complex VectorGridFunctions.
template <typename T>
VectorGridFunction<complex<T>> operator*(T A, VectorGridFunction<complex<T>> vgf)
//for easy multiplication in rk4 routine
{
  VectorGridFunction<complex<T>> vgfprod(0, vgf.GFvecDim(), vgf.GFarrDim());
  for(int i = 0; i < vgf.VGFdim(); i++){
    vgfprod.append(A * vgf.get(i));
  }
  return vgfprod;
}

  

