
#include <iostream>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::fstream;
using std::ifstream;
using std::ofstream;

#include <string>
using std::getline;
using std::string;

struct scheme_parameters {
  static const int stages = 3;
  int rotate[stages] = {22, 4, 40};
  int offset[stages] = {2, 4, 8};
};

/**
 * function_identifier: offsets a string by a number
 * parameters: string,integer
 * return value: string 
 */

string offset(string message, int offset) {
   string offsetted="";
    for (int i = 0 ; i < message.length();i++){ //go thru the messase
    char m = message[i];//each i is a character
    if(m+offset>127){
     offsetted += (m+offset)%128;
    }else if (m+offset<0){
      offsetted += (m+offset)%128;
    }
    else{
        offsetted+=(m+offset)%128;
    }
  }
  return offsetted;//return offset string
}

/**
 * function_identifier: prints message everyway sd
 * parameters: n/a
 * return value: n/a
 */

void offset_encryption() {
  int s = 5;
  string message = "The orange cat, sleeping quietly, awoke.";
  cout<<"Text : " <<message<<endl;
  string encrypted=offset(message,s);
  cout<<"\nCipher: "<< encrypted<<endl;
  cout<<"\nDecipher: "<<offset(encrypted,-s)<<endl;
  cout<<endl;
  cout<<endl;
}

/**
 * function_identifier: try to open file
 * parameters: string
 * return value: ifstream
 */
ifstream _open_input_file(string filename) {
  ifstream reader;
  reader.open(filename);
  if(!reader){
    cout<<"ERROR: Could not open file :"<<filename<<endl;
    exit(-1);
  }
  return reader;
}

/**
 * function_identifier: checking cmd line
 * parameters: argc,argv
 * return value: ifstream
 */
ifstream open_argv_file(int argc, const char** argv) {
  string filename="";
  if(argc!=2){
    cout<<"Error: incorrect usage!\n./a.out <filename>"<<endl;
    exit(-1);
  }else{
   filename = argv[1];
  return _open_input_file(filename);
  }
}

/**
 * function_identifier: prompting and open input file
 * parameters: n/a
 * return value: n/a
 */
ifstream open_input_file() {
  // Your Code Here
  string filename="";
  cout<<"Please enter the name of your input file: "; //<<endl;
  cin >> filename;
  return _open_input_file(filename);

}

/**
 * function_identifier: writes to file
 * parameters: string
 * return value: ofstream
 */
ofstream _open_output_file(string file_name) {
  ofstream output;
  output.open(file_name);
  if(!output){
    cout<<"ERROR: Could not open file :"<<file_name<<endl;
    exit(-1);
  }
  return output;
}


/**
 * function_identifier: takes in filename
 * parameters: n/a
 * return value:n/a
 */
ofstream open_output_file() {
  string filename="";
  //ISSUE starrs
  cout<<"Please enter the name of your output file: "; //<<endl;
  cin >> filename;
  return _open_output_file(filename);

}

/**
 * function_identifier: writes to file
 * parameters: ofstream,ifstream
 * return value: n/a
 */
void sequential_file_encryption(ofstream output,ifstream input) {
  int offset_value;
  string input_stream;
  cout << "What is your shift key? ";
  cin >> offset_value;
  string line="";
  while(!input.eof()){
    getline(input,line);
    output<<offset(line,offset_value)<<endl;
  }
  input.close();
  output.close();
}

/**
 * @brief 
 *
 * @param 
 * @param 
 * @return string
 *
 * @details
 * 
 *  Remember, no:
 *  1) Use of modulus or division operations within looping constructs
 *  2) Rotations greater than the length of the array must be reduced
 *  3) multiple iterations over the same elements of either array
 *  4) No built in functions other than length
 * 
 *  Engaging in any subset of these restrictions will result in 0 points
 */
/**
 * function_identifier: rotates string
 * parameters: string,int
 * return value: string 
 */
string rotate(string old, int offset) {
  string nwstring =old;
  int length = old.length();
  for (int i = 0 ; i<length;i++ ){
      if(offset+i>=length){  //offset+index >= length
         nwstring[i+offset-length]=old[i]; 
      }else if(i+offset<0){
        nwstring[i+offset+length]=old[i];
      }
      else{
         nwstring[i+offset]=old[i]; 
      } 
  }
    return nwstring;

}

/**
 * function_identifier: ecryp/decry funcrtion
 * parameters: string
 * return value: string 
 */
string rotation_encryption(string message) {
  scheme_parameters es;
  char scheme;

  cout << "Are you encrypting(E) or decrypting(D)? ";
  cin >> scheme;

  if (scheme == 'E' || scheme == 'e') {
    for(int i = 0 ; i<es.stages ; i++){
      message=rotate(message,es.rotate[i]);
      message=offset(message,es.offset[i]);
    }
  } else if (scheme == 'D' || scheme == 'd') {
   for(int i = es.stages-1 ; i >=0 ; i--){
      message=offset(message,-1*es.offset[i]);
      message=rotate(message,-1*es.rotate[i]);
    }
  } else {
    cerr << "ERROR: Encryption scheme unrecognized!" << endl;
  }
  return message;
}

/**
 * function_identifier: uses encry/decryp function
 * parameters: n/a
 * return value: n/a
 */
void rotation_file_encryption() {
  ofstream writer;
  string message;
  ifstream input = open_input_file();
  getline(input, message);
  writer.open("message.txt");
  writer<<rotation_encryption(message)<<endl;
}

int main(int argc, char const** argv) {
  offset_encryption();

  sequential_file_encryption
  (open_output_file(),open_argv_file(argc, argv));

  rotation_file_encryption();

  return 0;
}
