/* Example
 * Parsing Branch Traces
 */
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include <vector>
using namespace std;
string file;
unsigned long long addr;
string behavior, line;
unsigned long long target;
unsigned long long correct = 0;
unsigned long long total = 0;
std::ofstream fout("output.txt");
void alwaystaken(string file, std::ofstream& fout){

  ifstream infile(file);
  correct =0;
  total =0;
    while(getline(infile, line)) {
      total++;
      // Now we have to parse the line into it's two pieces
      stringstream s(line);
      s >> std::hex >> addr >> behavior >> std::hex >> target;
      // Now we can output it
      if(behavior == "T") {
        correct++; 
      }
    }

    fout << correct << "," << total << ";" ;
    fout <<endl;
  }
void alwaysnontaken(string file, std::ofstream& fout){
  ifstream infile(file);

    correct =0;
    total=0;
    while(getline(infile, line)) {
      total++;
      // Now we have to parse the line into it's two pieces
      stringstream s(line);
      s >> std::hex >> addr >> behavior >> std::hex >> target;
      // Now we can output it
      if(behavior == "NT") {  
        correct++;
      }
    }
    fout << correct << "," << total << ";" ;
    fout << endl;
  }

void singlebit(string file, std::ofstream& fout) {
  ifstream infile(file);
    correct =0;
    total=0;
    int index = 0;
    //creating vectors and populating with T
      vector<string> bit16(16,"T");
      vector<string> bit32(32,"T");
      vector<string> bit128(128,"T");
      vector<string> bit256(256,"T");
      vector<string> bit512(512,"T");
      vector<string> bit1024(1024,"T");
      vector<string> bit2048(2048,"T");
//16 bit check
    while(getline(infile, line)) {
      total ++;
      stringstream s(line);
      s >> std::hex >> addr >> behavior >> std::hex >> target;
      //bit mask first 4 bits
      index = addr & 15;
      //if correct, increment, else change prediction
      if(behavior == bit16.at(index)){
          correct ++;
      }else{
        bit16.at(index) = behavior;
      }
    }
    fout << correct << "," << total << "; " ;

    // cout << "16bit table: " ;
    // cout << correct <<" : " << total ;
  infile.close();
  infile.open(file);

//32 bit check
    correct = 0;
    total = 0;
    while(getline(infile, line)) {
      total ++;
      stringstream s(line);
      s >> std::hex >> addr >> behavior >> std::hex >> target;
      index= addr & 31;
      if(behavior == bit32.at(index)){
          correct ++;
      }else{
        bit32.at(index) = behavior;
      }
    }
    fout << correct << "," << total << "; " ;
  infile.close();
  infile.open(file);

//128 bit check
    correct = 0;
    total = 0;
    while(getline(infile, line)) {
      total ++;
      stringstream s(line);
      s >> std::hex >> addr >> behavior >> std::hex >> target;
      index = addr & 127;
      if(behavior == bit128.at(index)){
          correct ++;
      }else{
        bit128.at(index) = behavior;
      }
    }
    fout << correct << "," << total << "; " ;


  infile.close();
  infile.open(file);  

//256 bit check
    correct = 0;
    total = 0;
    while(getline(infile, line)) {
      total ++;
      stringstream s(line);
      s >> std::hex >> addr >> behavior >> std::hex >> target;
      index = addr & 255;
      if(behavior == bit256.at(index)){
          correct ++;
      }else{
        bit256.at(index) = behavior;
      }
    }
    fout << correct << "," << total << "; " ;


  infile.close();
  infile.open(file); 

//512 bit check

    correct = 0;
    total = 0;
    while(getline(infile, line)) {
      total ++;
      stringstream s(line);
      s >> std::hex >> addr >> behavior >> std::hex >> target;
      index = addr & 511;
      if(behavior == bit512.at(index)){
          correct ++;
      }else{
        bit512.at(index) = behavior;
      }
    }
    fout << correct << "," << total << "; " ;


  infile.close();
  infile.open(file); 

//1024 bit check
    correct = 0;
    total = 0;
    while(getline(infile, line)) {
      total ++;
      stringstream s(line);
      s >> std::hex >> addr >> behavior >> std::hex >> target;
      index = addr & 1023;
      if(behavior == bit1024.at(index)){
          correct ++;
      }else{
        bit1024.at(index) = behavior;
      }
    }
    fout << correct << "," << total << "; " ;


  infile.close();
  infile.open(file); 

//2048 bit check
    correct = 0;
    total = 0;
    while(getline(infile, line)) {
      total ++;
      stringstream s(line);
      s >> std::hex >> addr >> behavior >> std::hex >> target;
      index = addr & 2047;
      if(behavior == bit2048.at(index)){
          correct ++;
      }else{
        bit2048.at(index) = behavior;
      }
    }
    fout << correct << "," << total << ";" ;
    fout <<endl;

  infile.close();
  infile.open(file); 
}
void twobit(string file, std::ofstream& fout) {
  ifstream infile(file);
    correct =0;
    total=0;
    int index = 0;
    //creating vectors and populating with T
      vector<string> bit16(16,"ST");
      vector<string> bit32(32,"ST");
      vector<string> bit128(128,"ST");
      vector<string> bit256(256,"ST");
      vector<string> bit512(512,"ST");
      vector<string> bit1024(1024,"ST");
      vector<string> bit2048(2048,"ST");
//16 bit check
    while(getline(infile, line)) {
      total ++;
      stringstream s(line);
      s >> std::hex >> addr >> behavior >> std::hex >> target;
      //bit mask first 4 bits
      index = addr & 15;
      //if correct, increment, else change prediction
      if(behavior == "T" && (bit16.at(index) == "WT"|| bit16.at(index) == "ST")){
          correct ++;
          if(bit16.at(index) == "WT"){
            bit16.at(index) = "ST";
          }
      }else if(behavior == "NT" && (bit16.at(index) == "WNT" || bit16.at(index) == "SNT")){
        correct ++;
          if(bit16.at(index) == "WNT"){
            bit16.at(index) = "SNT";
          }
      }
      //then we are wrong
      //if we are wrong and the correct answer was NT
      else if(behavior == "NT"){
        //then the index must be either weakly taken, or strongly taken
        //if weakly taken
        if(bit16.at(index) == "WT"){
          //change to weakly not taken
          bit16.at(index) = "WNT";
        }else{
          //else change to weakly taken
          bit16.at(index) = "WT";
        }
      }
      //otherwise, we have taken behavior and are wrong
      else if(behavior == "T"){
        //if the prediction was weakly not taken
        if(bit16.at(index) == "WNT"){
          //change to weakly taken
          bit16.at(index) = "WT";
        }else{
          //otherwise we must have been at strongly not taken, and must shift down to weakly not taken
          bit16.at(index) = "WNT";
        }
      }
    }
    fout << correct << "," << total << "; " ;

  infile.close();
  infile.open(file);

//32 bit check
    correct =0;
    total=0;
    while(getline(infile, line)) {
      total ++;
      stringstream s(line);
      s >> std::hex >> addr >> behavior >> std::hex >> target;
      //bit mask first 4 bits
      index = addr & 31;
      //if correct, increment, else change prediction
      if(behavior == "T" && (bit32.at(index) == "WT"|| bit32.at(index) == "ST")){
          correct ++;
          if(bit32.at(index) == "WT"){
            bit32.at(index) = "ST";
          }
      }else if(behavior == "NT" && (bit32.at(index) == "WNT" || bit32.at(index) == "SNT")){
        correct ++;
          if(bit32.at(index) == "WNT"){
            bit32.at(index) = "SNT";
          }
      }
      //then we are wrong
      //if we are wrong and the correct answer was NT
      else if(behavior == "NT"){
        //then the index must be either weakly taken, or strongly taken
        //if weakly taken
        if(bit32.at(index) == "WT"){
          //change to weakly not taken
          bit32.at(index) = "WNT";
        }else{
          //else change to weakly taken
          bit32.at(index) = "WT";
        }
      }
      //otherwise, we have taken behavior and are wrong
      else if(behavior == "T"){
        //if the prediction was weakly not taken
        if(bit32.at(index) == "WNT"){
          //change to weakly taken
          bit32.at(index) = "WT";
        }else{
          //otherwise we must have been at strongly not taken, and must shift down to weakly not taken
          bit32.at(index) = "WNT";
        }
      }
    }
    fout << correct << "," << total << "; " ;


  infile.close();
  infile.open(file);

//128 bit check
    correct = 0;
    total = 0;
    while(getline(infile, line)) {
      total ++;
      stringstream s(line);
      s >> std::hex >> addr >> behavior >> std::hex >> target;
      index = addr & 127;
      if(behavior == "T" && (bit128.at(index) == "WT"|| bit128.at(index) == "ST")){
          correct ++;
          if(bit128.at(index) == "WT"){
            bit128.at(index) = "ST";
          }
      }else if(behavior == "NT" && (bit128.at(index) == "WNT" || bit128.at(index) == "SNT")){
        correct ++;
          if(bit128.at(index) == "WNT"){
            bit128.at(index) = "SNT";
          }
      }
      //then we are wrong
      //if we are wrong and the correct answer was NT
      else if(behavior == "NT"){
        //then the index must be either weakly taken, or strongly taken
        //if weakly taken
        if(bit128.at(index) == "WT"){
          //change to weakly not taken
          bit128.at(index) = "WNT";
        }else{
          //else change to weakly taken
          bit128.at(index) = "WT";
        }
      }
      //otherwise, we have taken behavior and are wrong
      else if(behavior == "T"){
        //if the prediction was weakly not taken
        if(bit128.at(index) == "WNT"){
          //change to weakly taken
          bit128.at(index) = "WT";
        }else{
          //otherwise we must have been at strongly not taken, and must shift down to weakly not taken
          bit128.at(index) = "WNT";
        }
      }
    }
   fout << correct << "," << total << "; " ;


  infile.close();
  infile.open(file);  

  //256 bit check
    correct = 0;
    total = 0;
    while(getline(infile, line)) {
      total ++;
      stringstream s(line);
      s >> std::hex >> addr >> behavior >> std::hex >> target;
      index = addr & 255;
      //if correct, increment, else change prediction
      if(behavior == "T" && (bit256.at(index) == "WT"|| bit256.at(index) == "ST")){
          correct ++;
          if(bit256.at(index) == "WT"){
            bit256.at(index) = "ST";
          }
      }else if(behavior == "NT" && (bit256.at(index) == "WNT" || bit256.at(index) == "SNT")){
        correct ++;
          if(bit256.at(index) == "WNT"){
            bit256.at(index) = "SNT";
          }
      }
      //then we are wrong
      //if we are wrong and the correct answer was NT
      else if(behavior == "NT"){
        //then the index must be either weakly taken, or strongly taken
        //if weakly taken
        if(bit256.at(index) == "WT"){
          //change to weakly not taken
          bit256.at(index) = "WNT";
        }else{
          //else change to weakly taken
          bit256.at(index) = "WT";
        }
      }
      //otherwise, we have taken behavior and are wrong
      else if(behavior == "T"){
        //if the prediction was weakly not taken
        if(bit256.at(index) == "WNT"){
          //change to weakly taken
          bit256.at(index) = "WT";
        }else{
          //otherwise we must have been at strongly not taken, and must shift down to weakly not taken
          bit256.at(index) = "WNT";
        }
      }
    }
    fout << correct << "," << total << "; " ;


  infile.close();
  infile.open(file); 

//512 bit check
    correct = 0;
    total = 0;
    while(getline(infile, line)) {
      total ++;
      stringstream s(line);
      s >> std::hex >> addr >> behavior >> std::hex >> target;
      index = addr & 511;
      //if correct, increment, else change prediction
      if(behavior == "T" && (bit512.at(index) == "WT"|| bit512.at(index) == "ST")){
          correct ++;
          if(bit512.at(index) == "WT"){
            bit512.at(index) = "ST";
          }
      }else if(behavior == "NT" && (bit512.at(index) == "WNT" || bit512.at(index) == "SNT")){
        correct ++;
          if(bit512.at(index) == "WNT"){
            bit512.at(index) = "SNT";
          }
      }
      //then we are wrong
      //if we are wrong and the correct answer was NT
      else if(behavior == "NT"){
        //then the index must be either weakly taken, or strongly taken
        //if weakly taken
        if(bit512.at(index) == "WT"){
          //change to weakly not taken
          bit512.at(index) = "WNT";
        }else{
          //else change to weakly taken
          bit512.at(index) = "WT";
        }
      }
      //otherwise, we have taken behavior and are wrong
      else if(behavior == "T"){
        //if the prediction was weakly not taken
        if(bit512.at(index) == "WNT"){
          //change to weakly taken
          bit512.at(index) = "WT";
        }else{
          //otherwise we must have been at strongly not taken, and must shift down to weakly not taken
          bit512.at(index) = "WNT";
        }
      }
    }
    fout << correct << "," << total << "; " ;


  infile.close();
  infile.open(file); 

//1024 bit check
    correct = 0;
    total = 0;
    while(getline(infile, line)) {
      total ++;
      stringstream s(line);
      s >> std::hex >> addr >> behavior >> std::hex >> target;
      index = addr & 1023;
       //if correct, increment, else change prediction
      if(behavior == "T" && (bit1024.at(index) == "WT"|| bit1024.at(index) == "ST")){
          correct ++;
          if(bit1024.at(index) == "WT"){
            bit1024.at(index) = "ST";
          }
      }else if(behavior == "NT" && (bit1024.at(index) == "WNT" || bit1024.at(index) == "SNT")){
        correct ++;
          if(bit1024.at(index) == "WNT"){
            bit1024.at(index) = "SNT";
          }
      }
      //then we are wrong
      //if we are wrong and the correct answer was NT
      else if(behavior == "NT"){
        //then the index must be either weakly taken, or strongly taken
        //if weakly taken
        if(bit1024.at(index) == "WT"){
          //change to weakly not taken
          bit1024.at(index) = "WNT";
        }else{
          //else change to weakly taken
          bit1024.at(index) = "WT";
        }
      }
      //otherwise, we have taken behavior and are wrong
      else if(behavior == "T"){
        //if the prediction was weakly not taken
        if(bit1024.at(index) == "WNT"){
          //change to weakly taken
          bit1024.at(index) = "WT";
        }else{
          //otherwise we must have been at strongly not taken, and must shift down to weakly not taken
          bit1024.at(index) = "WNT";
        }
    }
  }
    fout << correct << "," << total << "; " ;


  infile.close();
  infile.open(file); 

//2048 bit check
    correct = 0;
    total = 0;
    while(getline(infile, line)) {
      total ++;
      stringstream s(line);
      s >> std::hex >> addr >> behavior >> std::hex >> target;
      index = addr & 2047;
      //if correct, increment, else change prediction
      if(behavior == "T" && (bit2048.at(index) == "WT"|| bit2048.at(index) == "ST")){
          correct ++;
          if(bit2048.at(index) == "WT"){
            bit2048.at(index) = "ST";
          }
      }else if(behavior == "NT" && (bit2048.at(index) == "WNT" || bit2048.at(index) == "SNT")){
        correct ++;
          if(bit2048.at(index) == "WNT"){
            bit2048.at(index) = "SNT";
          }
      }
      //then we are wrong
      //if we are wrong and the correct answer was NT
      else if(behavior == "NT"){
        //then the index must be either weakly taken, or strongly taken
        //if weakly taken
        if(bit2048.at(index) == "WT"){
          //change to weakly not taken
          bit2048.at(index) = "WNT";
        }else{
          //else change to weakly taken
          bit2048.at(index) = "WT";
        }
      }
      //otherwise, we have taken behavior and are wrong
      else if(behavior == "T"){
        //if the prediction was weakly not taken
        if(bit2048.at(index) == "WNT"){
          //change to weakly taken
          bit2048.at(index) = "WT";
        }else{
          //otherwise we must have been at strongly not taken, and must shift down to weakly not taken
          bit2048.at(index) = "WNT";
        }
    }
    }
    fout << correct << "," << total << ";" ;
    fout <<endl;


  infile.close();
  infile.open(file); 

}
void gshare(string file, std::ofstream& fout){
  int fghr = 0;
  int i;
  ifstream infile(file);
//3 bit ghr
    correct =0;
    total=0;
    int index = 0;
    vector<int> ghr3(3,0);
  vector<string> bit2048(2048,"ST");
  //3 bit ghr check
    correct = 0;
    total = 0;
    while(getline(infile, line)) {
      total ++;
      stringstream s(line);
      s >> std::hex >> addr >> behavior >> std::hex >> target;
      //get last few bits
      index = addr & 2047;
      // convert GHR bits to an integer
      fghr = (ghr3[0] << 2) | (ghr3[1] << 1) | ghr3[2];
      //xor against ghr
      index = (index ^ fghr);

      //if correct, increment
      if(behavior == "T" && (bit2048.at(index) == "WT"|| bit2048.at(index) == "ST")){
          correct ++;
          if(bit2048.at(index) == "WT"){
            bit2048.at(index) = "ST";
          }
      }else if(behavior == "NT" && (bit2048.at(index) == "WNT" || bit2048.at(index) == "SNT")){
        correct ++;
          if(bit2048.at(index) == "WNT"){
            bit2048.at(index) = "SNT";
          }
      }
      //else we are wrong
      else if(behavior == "NT"){//if we are wrong and the correct answer was NT
        //then the index must be either weakly taken, or strongly taken
        if(bit2048.at(index) == "WT"){//if weakly taken
          //change to weakly not taken
          bit2048.at(index) = "WNT";
        }else{
          //else change to weakly taken
          bit2048.at(index) = "WT";
        }
      }
      //otherwise, we have taken behavior and are wrong
      else if(behavior == "T"){
        //if the prediction was weakly not taken
        if(bit2048.at(index) == "WNT"){
          //change to weakly taken
          bit2048.at(index) = "WT";
        }else{
          //otherwise we must have been at strongly not taken, and must shift down to weakly not taken
          bit2048.at(index) = "WNT";
        }
      }
    
      //now we want to shift ghr to the left
      //go through the ghr vector +1 because were tossing the oldest bit
      for( i=1; i<ghr3.size(); i++){
          ghr3.at(i-1) = ghr3.at(i);
        }
      //now if ghr behavior was T, set 
      if(behavior == "T"){
        ghr3.at(ghr3.size()-1) = 1;
      }
      else{ 
        ghr3.at(ghr3.size()-1) = 0;
      }

    }
    fout << correct << "," << total << "; " ;


  infile.close();
  infile.open(file); 
//FOUR BIT GHRe
  vector<int> ghr4(4,0);
  for(i =0; i<bit2048.size();i++) {
    bit2048.at(i) = "ST";
  }
  //2048 bit check
    correct = 0;
    total = 0;
    while(getline(infile, line)) {
      total ++;
      stringstream s(line);
      s >> std::hex >> addr >> behavior >> std::hex >> target;
      //get last few bits
      index = addr & 2047;
      // convert GHR bits to an integer
      fghr = (ghr4[0] << 3) | (ghr4[1] << 2) | (ghr4[2] << 1) | ghr4[3];
      //xor against ghr
      index = (index ^ fghr);

      //if correct, increment
      if(behavior == "T" && (bit2048.at(index) == "WT"|| bit2048.at(index) == "ST")){
          correct ++;
          if(bit2048.at(index) == "WT"){
            bit2048.at(index) = "ST";
          }
      }else if(behavior == "NT" && (bit2048.at(index) == "WNT" || bit2048.at(index) == "SNT")){
        correct ++;
          if(bit2048.at(index) == "WNT"){
            bit2048.at(index) = "SNT";
          }
      }
      //then we are wrong
      //if we are wrong and the correct answer was NT
      else if(behavior == "NT"){
        //then the index must be either weakly taken, or strongly taken
        //if weakly taken
        if(bit2048.at(index) == "WT"){
          //change to weakly not taken
          bit2048.at(index) = "WNT";
        }else{
          //else change to weakly taken
          bit2048.at(index) = "WT";
        }
      }
      //otherwise, we have taken behavior and are wrong
      else if(behavior == "T"){
        //if the prediction was weakly not taken
        if(bit2048.at(index) == "WNT"){
          //change to weakly taken
          bit2048.at(index) = "WT";
        }else{
          //otherwise we must have been at strongly not taken, and must shift down to weakly not taken
          bit2048.at(index) = "WNT";
        }
      }
    
      //now we want to shift ghr to the left
      //go through the ghr vector +1 because were tossing the oldest bit
      for( i=1; i<ghr4.size(); i++){
          ghr4.at(i-1) = ghr4.at(i);
        }
      //now if ghr behavior was T, set 
      if(behavior == "T"){
        ghr4.at(ghr4.size()-1) = 1;
      }
      else{ 
        ghr4.at(ghr4.size()-1) = 0;
      }

    }
   fout << correct << "," << total << "; " ;


  infile.close();
  infile.open(file); 
//FIVE BIT GHR
    vector<int> ghr5(5,0);
  for(i =0; i<bit2048.size();i++) {
    bit2048.at(i) = "ST";
  }
  //2048 bit check
    correct = 0;
    total = 0;
    while(getline(infile, line)) {
      total ++;
      stringstream s(line);
      s >> std::hex >> addr >> behavior >> std::hex >> target;
      //get last few bits
      index = addr & 2047;
      // convert GHR bits to an integer
      fghr = (ghr5[0] << 4) | (ghr5[1] << 3) | (ghr5[2] << 2) | (ghr5[3] << 1) | ghr5[4];
      //xor against ghr
      index = (index ^ fghr);

      //if correct, increment
      if(behavior == "T" && (bit2048.at(index) == "WT"|| bit2048.at(index) == "ST")){
          correct ++;
          if(bit2048.at(index) == "WT"){
            bit2048.at(index) = "ST";
          }
      }else if(behavior == "NT" && (bit2048.at(index) == "WNT" || bit2048.at(index) == "SNT")){
        correct ++;
          if(bit2048.at(index) == "WNT"){
            bit2048.at(index) = "SNT";
          }
      }
      //then we are wrong
      //if we are wrong and the correct answer was NT
      else if(behavior == "NT"){
        //then the index must be either weakly taken, or strongly taken
        //if weakly taken
        if(bit2048.at(index) == "WT"){
          //change to weakly not taken
          bit2048.at(index) = "WNT";
        }else{
          //else change to weakly taken
          bit2048.at(index) = "WT";
        }
      }
      //otherwise, we have taken behavior and are wrong
      else if(behavior == "T"){
        //if the prediction was weakly not taken
        if(bit2048.at(index) == "WNT"){
          //change to weakly taken
          bit2048.at(index) = "WT";
        }else{
          //otherwise we must have been at strongly not taken, and must shift down to weakly not taken
          bit2048.at(index) = "WNT";
        }
      }
    
      //now we want to shift ghr to the left
      //go through the ghr vector +1 because were tossing the oldest bit
      for( i=1; i<ghr5.size(); i++){
          ghr5.at(i-1) = ghr5.at(i);
        }
      //now if ghr behavior was T, set 
      if(behavior == "T"){
        ghr5.at(ghr5.size()-1) = 1;
      }
      else{ 
        ghr5.at(ghr5.size()-1) = 0;
      }

    }
  fout << correct << "," << total << "; " ;


  infile.close();
  infile.open(file); 

//SIX BIT 
   vector<int> ghr6(6,0);
  for(i =0; i<bit2048.size();i++) {
    bit2048.at(i) = "ST";
  }
  //2048 bit check
    correct = 0;
    total = 0;
    while(getline(infile, line)) {
      total ++;
      stringstream s(line);
      s >> std::hex >> addr >> behavior >> std::hex >> target;
      //get last few bits
      index = addr & 2047;
      // convert GHR bits to an integer
      fghr = (ghr6[0] << 5) | (ghr6[1] << 4) | (ghr6[2] << 3) | (ghr6[3] << 2) | (ghr6[4] << 1) | ghr6[5];
      //xor against ghr
      index = (index ^ fghr);

      //if correct, increment
      if(behavior == "T" && (bit2048.at(index) == "WT"|| bit2048.at(index) == "ST")){
          correct ++;
          if(bit2048.at(index) == "WT"){
            bit2048.at(index) = "ST";
          }
      }else if(behavior == "NT" && (bit2048.at(index) == "WNT" || bit2048.at(index) == "SNT")){
        correct ++;
          if(bit2048.at(index) == "WNT"){
            bit2048.at(index) = "SNT";
          }
      }
      //then we are wrong
      //if we are wrong and the correct answer was NT
      else if(behavior == "NT"){
        //then the index must be either weakly taken, or strongly taken
        //if weakly taken
        if(bit2048.at(index) == "WT"){
          //change to weakly not taken
          bit2048.at(index) = "WNT";
        }else{
          //else change to weakly taken
          bit2048.at(index) = "WT";
        }
      }
      //otherwise, we have taken behavior and are wrong
      else if(behavior == "T"){
        //if the prediction was weakly not taken
        if(bit2048.at(index) == "WNT"){
          //change to weakly taken
          bit2048.at(index) = "WT";
        }else{
          //otherwise we must have been at strongly not taken, and must shift down to weakly not taken
          bit2048.at(index) = "WNT";
        }
      }
    
      //now we want to shift ghr to the left
      //go through the ghr vector +1 because were tossing the oldest bit
      for( i=1; i<ghr6.size(); i++){
          ghr6.at(i-1) = ghr6.at(i);
        }
      //now if ghr behavior was T, set 
      if(behavior == "T"){
        ghr6.at(ghr6.size()-1) = 1;
      }
      else{ 
        ghr6.at(ghr6.size()-1) = 0;
      }

    }
    fout << correct << "," << total << "; " ;

  infile.close();
  infile.open(file); 

//SEVEN BIT GHR
   vector<int> ghr7(7,0);
  for(i =0; i<bit2048.size();i++) {
    bit2048.at(i) = "ST";
  }
  //2048 bit check
    correct = 0;
    total = 0;
    while(getline(infile, line)) {
      total ++;
      stringstream s(line);
      s >> std::hex >> addr >> behavior >> std::hex >> target;
      //get last few bits
      index = addr & 2047;
      // convert GHR bits to an integer
      fghr = (ghr7[0] << 6) | (ghr7[1] << 5) | (ghr7[2] << 4) | (ghr7[3] << 3) | (ghr7[4] << 2) | (ghr7[5] << 1) | ghr7[6];
      //xor against ghr
      index = (index ^ fghr);

      //if correct, increment
      if(behavior == "T" && (bit2048.at(index) == "WT"|| bit2048.at(index) == "ST")){
          correct ++;
          if(bit2048.at(index) == "WT"){
            bit2048.at(index) = "ST";
          }
      }else if(behavior == "NT" && (bit2048.at(index) == "WNT" || bit2048.at(index) == "SNT")){
        correct ++;
          if(bit2048.at(index) == "WNT"){
            bit2048.at(index) = "SNT";
          }
      }
      //then we are wrong
      //if we are wrong and the correct answer was NT
      else if(behavior == "NT"){
        //then the index must be either weakly taken, or strongly taken
        //if weakly taken
        if(bit2048.at(index) == "WT"){
          //change to weakly not taken
          bit2048.at(index) = "WNT";
        }else{
          //else change to weakly taken
          bit2048.at(index) = "WT";
        }
      }
      //otherwise, we have taken behavior and are wrong
      else if(behavior == "T"){
        //if the prediction was weakly not taken
        if(bit2048.at(index) == "WNT"){
          //change to weakly taken
          bit2048.at(index) = "WT";
        }else{
          //otherwise we must have been at strongly not taken, and must shift down to weakly not taken
          bit2048.at(index) = "WNT";
        }
      }
    
      //now we want to shift ghr to the left
      //go through the ghr vector +1 because were tossing the oldest bit
      for( i=1; i<ghr7.size(); i++){
          ghr7.at(i-1) = ghr7.at(i);
        }
      //now if ghr behavior was T, set 
      if(behavior == "T"){
        ghr7.at(ghr7.size()-1) = 1;
      }
      else{ 
        ghr7.at(ghr7.size()-1) = 0;
      }

    }
    fout << correct << "," << total << "; " ;

  infile.close();
  infile.open(file); 

//eight BIT GHR
   vector<int> ghr8(8,0);
  for(i =0; i<bit2048.size();i++) {
    bit2048.at(i) = "ST";
  }
  //2048 bit check
    correct = 0;
    total = 0;
    while(getline(infile, line)) {
      total ++;
      stringstream s(line);
      s >> std::hex >> addr >> behavior >> std::hex >> target;
      //get last few bits
      index = addr & 2047;
      // convert GHR bits to an integer
      fghr = (ghr8[0] << 7) | (ghr8[1] << 6) | (ghr8[2] << 5) | (ghr8[3] << 4) | (ghr8[4] << 3) | (ghr8[5] << 2) | (ghr8[6] << 1) | ghr8[7];
      //xor against ghr
      index = (index ^ fghr);

      //if correct, increment
      if(behavior == "T" && (bit2048.at(index) == "WT"|| bit2048.at(index) == "ST")){
          correct ++;
          if(bit2048.at(index) == "WT"){
            bit2048.at(index) = "ST";
          }
      }else if(behavior == "NT" && (bit2048.at(index) == "WNT" || bit2048.at(index) == "SNT")){
        correct ++;
          if(bit2048.at(index) == "WNT"){
            bit2048.at(index) = "SNT";
          }
      }
      //then we are wrong
      //if we are wrong and the correct answer was NT
      else if(behavior == "NT"){
        //then the index must be either weakly taken, or strongly taken
        //if weakly taken
        if(bit2048.at(index) == "WT"){
          //change to weakly not taken
          bit2048.at(index) = "WNT";
        }else{
          //else change to weakly taken
          bit2048.at(index) = "WT";
        }
      }
      //otherwise, we have taken behavior and are wrong
      else if(behavior == "T"){
        //if the prediction was weakly not taken
        if(bit2048.at(index) == "WNT"){
          //change to weakly taken
          bit2048.at(index) = "WT";
        }else{
          //otherwise we must have been at strongly not taken, and must shift down to weakly not taken
          bit2048.at(index) = "WNT";
        }
      }
    
      //now we want to shift ghr to the left
      //go through the ghr vector +1 because were tossing the oldest bit
      for( i=1; i<ghr8.size(); i++){
          ghr8.at(i-1) = ghr8.at(i);
        }
      //now if ghr behavior was T, set 
      if(behavior == "T"){
        ghr8.at(ghr8.size()-1) = 1;
      }
      else{ 
        ghr8.at(ghr8.size()-1) = 0;
      }

    }
    fout << correct << "," << total << "; " ;


  infile.close();
  infile.open(file);

//NINE BIT GHR
   vector<int> ghr9(9,0);
  for(i =0; i<bit2048.size();i++) {
    bit2048.at(i) = "ST";
  }
  //2048 bit check
    correct = 0;
    total = 0;
    while(getline(infile, line)) {
      total ++;
      stringstream s(line);
      s >> std::hex >> addr >> behavior >> std::hex >> target;
      //get last few bits
      index = addr & 2047;
      // convert GHR bits to an integer
      fghr = (ghr9[0] << 8) | (ghr9[1] << 7) | (ghr9[2] << 6) | (ghr9[3] << 5) | (ghr9[4] << 4) | (ghr9[5] << 3) | (ghr9[6] << 2) | (ghr9[7] << 1) | ghr9[8];
      //xor against ghr
      index = (index ^ fghr);

      //if correct, increment
      if(behavior == "T" && (bit2048.at(index) == "WT"|| bit2048.at(index) == "ST")){
          correct ++;
          if(bit2048.at(index) == "WT"){
            bit2048.at(index) = "ST";
          }
      }else if(behavior == "NT" && (bit2048.at(index) == "WNT" || bit2048.at(index) == "SNT")){
        correct ++;
          if(bit2048.at(index) == "WNT"){
            bit2048.at(index) = "SNT";
          }
      }
      //then we are wrong
      //if we are wrong and the correct answer was NT
      else if(behavior == "NT"){
        //then the index must be either weakly taken, or strongly taken
        //if weakly taken
        if(bit2048.at(index) == "WT"){
          //change to weakly not taken
          bit2048.at(index) = "WNT";
        }else{
          //else change to weakly taken
          bit2048.at(index) = "WT";
        }
      }
      //otherwise, we have taken behavior and are wrong
      else if(behavior == "T"){
        //if the prediction was weakly not taken
        if(bit2048.at(index) == "WNT"){
          //change to weakly taken
          bit2048.at(index) = "WT";
        }else{
          //otherwise we must have been at strongly not taken, and must shift down to weakly not taken
          bit2048.at(index) = "WNT";
        }
      }
    
      //now we want to shift ghr to the left
      //go through the ghr vector +1 because were tossing the oldest bit
      for( i=1; i<ghr9.size(); i++){
          ghr9.at(i-1) = ghr9.at(i);
        }
      //now if ghr behavior was T, set 
      if(behavior == "T"){
        ghr9.at(ghr9.size()-1) = 1;
      }
      else{ 
        ghr9.at(ghr9.size()-1) = 0;
      }

    }
    fout << correct << "," << total << "; " ;


  infile.close();
  infile.open(file); 

//ten BIT GHR
   vector<int> ghr10(10,0);
  for(i =0; i<bit2048.size();i++) {
    bit2048.at(i) = "ST";
  }
  //2048 bit check
    correct = 0;
    total = 0;
    while(getline(infile, line)) {
      total ++;
      stringstream s(line);
      s >> std::hex >> addr >> behavior >> std::hex >> target;
      //get last few bits
      index = addr & 2047;
      // convert GHR bits to an integer
      fghr = (ghr10[0] << 9) | (ghr10[1] << 8) | (ghr10[2] << 7) | (ghr10[3] << 6) | (ghr10[4] << 5) | (ghr10[5] << 4) | (ghr10[6] << 3) | (ghr10[7] << 2) | (ghr10[8]<<1) | ghr10[9];
      //xor against ghr
      index = (index ^ fghr);

      //if correct, increment
      if(behavior == "T" && (bit2048.at(index) == "WT"|| bit2048.at(index) == "ST")){
          correct ++;
          if(bit2048.at(index) == "WT"){
            bit2048.at(index) = "ST";
          }
      }else if(behavior == "NT" && (bit2048.at(index) == "WNT" || bit2048.at(index) == "SNT")){
        correct ++;
          if(bit2048.at(index) == "WNT"){
            bit2048.at(index) = "SNT";
          }
      }
      //then we are wrong
      //if we are wrong and the correct answer was NT
      else if(behavior == "NT"){
        //then the index must be either weakly taken, or strongly taken
        //if weakly taken
        if(bit2048.at(index) == "WT"){
          //change to weakly not taken
          bit2048.at(index) = "WNT";
        }else{
          //else change to weakly taken
          bit2048.at(index) = "WT";
        }
      }
      //otherwise, we have taken behavior and are wrong
      else if(behavior == "T"){
        //if the prediction was weakly not taken
        if(bit2048.at(index) == "WNT"){
          //change to weakly taken
          bit2048.at(index) = "WT";
        }else{
          //otherwise we must have been at strongly not taken, and must shift down to weakly not taken
          bit2048.at(index) = "WNT";
        }
      }
    
      //now we want to shift ghr to the left
      //go through the ghr vector +1 because were tossing the oldest bit
      for( i=1; i<ghr10.size(); i++){
          ghr10.at(i-1) = ghr10.at(i);
        }
      //now if ghr behavior was T, set 
      if(behavior == "T"){
        ghr10.at(ghr10.size()-1) = 1;
      }
      else{ 
        ghr10.at(ghr10.size()-1) = 0;
      }

    }
   fout << correct << "," << total << "; " ;


  infile.close();
  infile.open(file);

//ELEVEN BIT GHR
   vector<int> ghr11(11,0);
  for(i =0; i<bit2048.size();i++) {
    bit2048.at(i) = "ST";
  }
  //2048 bit check
    correct = 0;
    total = 0;
    while(getline(infile, line)) {
      total ++;
      stringstream s(line);
      s >> std::hex >> addr >> behavior >> std::hex >> target;
      //get last few bits
      index = addr & 2047;
      // convert GHR bits to an integer
      fghr = (ghr11[0] << 10) | (ghr11[1] << 9) | (ghr11[2] << 8) | (ghr11[3] << 7) | (ghr11[4] << 6) | (ghr11[5] << 5) | (ghr11[6] << 4) | (ghr11[7] << 3) | (ghr11[8]<<2) | (ghr11[9] << 1) | ghr11[10];
      //xor against ghr
      index = (index ^ fghr);

      //if correct, increment
      if(behavior == "T" && (bit2048.at(index) == "WT"|| bit2048.at(index) == "ST")){
          correct ++;
          if(bit2048.at(index) == "WT"){
            bit2048.at(index) = "ST";
          }
      }else if(behavior == "NT" && (bit2048.at(index) == "WNT" || bit2048.at(index) == "SNT")){
        correct ++;
          if(bit2048.at(index) == "WNT"){
            bit2048.at(index) = "SNT";
          }
      }
      //then we are wrong
      //if we are wrong and the correct answer was NT
      else if(behavior == "NT"){
        //then the index must be either weakly taken, or strongly taken
        //if weakly taken
        if(bit2048.at(index) == "WT"){
          //change to weakly not taken
          bit2048.at(index) = "WNT";
        }else{
          //else change to weakly taken
          bit2048.at(index) = "WT";
        }
      }
      //otherwise, we have taken behavior and are wrong
      else if(behavior == "T"){
        //if the prediction was weakly not taken
        if(bit2048.at(index) == "WNT"){
          //change to weakly taken
          bit2048.at(index) = "WT";
        }else{
          //otherwise we must have been at strongly not taken, and must shift down to weakly not taken
          bit2048.at(index) = "WNT";
        }
      }
    
      //now we want to shift ghr to the left
      //go through the ghr vector +1 because were tossing the oldest bit
      for( i=1; i<ghr11.size(); i++){
          ghr11.at(i-1) = ghr11.at(i);
        }
      //now if ghr behavior was T, set 
      if(behavior == "T"){
        ghr11.at(ghr11.size()-1) = 1;
      }
      else{ 
        ghr11.at(ghr11.size()-1) = 0;
      }

    }
   fout << correct << "," << total << ";" ;
    fout <<endl;


  infile.close();
  infile.open(file);   
}
void tournament(string file, std::ofstream& fout){
  int fghr = 0;
  ifstream infile(file);

  int index = 0;
  int gShareIdx = 0;

  int bimodT = 0;
  int bimodNT = 0;
  int gShareT = 0;
  int gShareNT = 0;
  int i=0;
  int gShareCorrect = 0;
  int bimodCorrect = 0;

  string gSharePred, bimodPred, equalpred;

  vector<int> ghr11(11,0);
  vector<string> bimodTbl(2048,"ST");
  vector<string> gShareTbl(2048,"ST");
  vector<string> selectorTbl(2048,"SG");

  correct = 0;
  total = 0;
//ENTER FILE
  while(getline(infile, line)) {
    total ++;
    stringstream s(line);
    s >> std::hex >> addr >> behavior >> std::hex >> target;
    //get last few bits
    index = addr & 2047;
    // convert GHR bits to an integer
    fghr = (ghr11[0] << 10) | (ghr11[1] << 9) | (ghr11[2] << 8) | (ghr11[3] << 7) | (ghr11[4] << 6) | (ghr11[5] << 5) | (ghr11[6] << 4) | (ghr11[7] << 3) | (ghr11[8]<<2) | (ghr11[9] << 1) | ghr11[10];
    //xor against ghr
    gShareIdx = (index ^ fghr);
    // now that we have both indices
    //we will store both of their predictions
    gSharePred = gShareTbl.at(gShareIdx);
    bimodPred = bimodTbl.at(index);
    //storing intial prediction incase both are equal at the end
    equalpred = selectorTbl.at(index);
      
//GSHARE
  //IF PREDICTION IS CORRECT
  if( (behavior == "T" && (gSharePred == "WT"|| gSharePred == "ST")) || (behavior == "NT" && (gSharePred == "WNT" || gSharePred == "SNT")) ){
    //mark gShareCorrect 
    gShareCorrect = 1;
    //IF BEHAVIOR = TAKEN
    if(behavior == "T" && (gSharePred == "WT"|| gSharePred == "ST")){
      //if pred = WT, move next pred to ST
      if(gSharePred == "WT"){gShareTbl.at(gShareIdx) = "ST";}
    }
    //IF BEHAVIOR = NOT TAKEN
    else if(behavior == "NT" && (gSharePred == "WNT" || gSharePred == "SNT")){
      //if pred = WNT, move next pred to SNT
      if(gSharePred == "WNT"){gShareTbl.at(gShareIdx) = "SNT";}
    }
  }
  //IF PREDICTION IS INCORRECT
  else{
    //mark gShareCorrect to 0
    gShareCorrect = 0;
    // AND BEHAVIOR = NOT TAKEN
    if(behavior == "NT"){
      //if we were at WT, we can shift to WNT, else, we were at ST and need to shift to WT
      if(gSharePred == "WT"){gShareTbl.at(gShareIdx) = "WNT";}
      else{gShareTbl.at(gShareIdx) = "WT";}
    }
    //AND BEHAVIOR = TAKEN
    else if(behavior == "T"){
      // if behavior was WNT change to WT otherwise we must have been at strongly not taken, and must shift down to weakly not taken
      if(gSharePred == "WNT"){ gShareTbl.at(gShareIdx) = "WT"; }
      else{ gShareTbl.at(gShareIdx) = "WNT"; }
    }
  }
//BIMODAL
  //IF PREDICTION IS CORRECT
  if( (behavior == "T" && (bimodPred == "WT"|| bimodPred == "ST") ) || (behavior == "NT" && (bimodPred == "WNT" || bimodPred == "SNT") ) ){
    //mark bimodCorrect 
    bimodCorrect = 1;
    //IF BEHAVIOR = TAKEN
      if(behavior == "T" && (bimodPred == "WT"|| bimodPred == "ST")){
        //if pred = WT, move next pred to ST
        if(bimodPred == "WT"){bimodTbl.at(index) = "ST";}
      }
    //IF BEHAVIOR = NOT TAKEN
      else if(behavior == "NT" && (bimodPred == "WNT" || bimodPred == "SNT")){
        //if pred = WNT, move next pred to SNT
        if(bimodPred == "WNT"){bimodTbl.at(index) = "SNT";}
      }
  }
  //IF PREDICTION IS INCORRECT
  else{
    //mark bimodCorrect to 0
    bimodCorrect = 0;
    // AND BEHAVIOR = NOT TAKEN
      if(behavior == "NT"){
        //if we were at WT, we can shift to WNT, else, we were at ST and need to shift to WT
        if(bimodPred == "WT"){bimodTbl.at(index) = "WNT";}
        else{bimodTbl.at(index) = "WT";}
      }
    //AND BEHAVIOR = TAKEN
      else if(behavior == "T"){
        // if behavior was WNT change to WT otherwise we must have been at strongly not taken, and must shift down to weakly not taken
        if(bimodPred == "WNT"){ bimodTbl.at(index) = "WT"; }
        else{ bimodTbl.at(index) = "WNT"; }
      }
  }
//SHIFTING GSHARE AND BIMODAL
  //NOT TAKEN
  if(behavior == "NT"){
        //need to check if our bimodal index needs to be shifted towards NT                
        if(bimodPred == "ST"){bimodTbl.at(index) = "WT";}
        else if(bimodPred == "WT"){bimodTbl.at(index) = "WNT";}
        else if(bimodPred == "WNT"){bimodTbl.at(index) = "SNT";}
        //we also need to check if our gShare index needs to be shifted towards NT                
        if(gSharePred == "ST"){gShareTbl.at(gShareIdx) = "WT";}
        else if(gSharePred == "WT"){gShareTbl.at(gShareIdx) = "WNT";}
        else if(gSharePred == "WNT"){gShareTbl.at(gShareIdx) = "SNT";}
  }
  // TAKEN
  if(behavior == "T"){
        //to check if our bimodal index needs to be shifted                   
        if(bimodPred == "SNT"){bimodTbl.at(index) = "WNT";}
        else if(bimodPred == "WNT"){bimodTbl.at(index) = "WT";}
        else if(bimodPred == "WT"){bimodTbl.at(index) = "ST";}
      
        //to check if our gShare index needs to be shifted                   
        if(gSharePred == "SNT"){gShareTbl.at(gShareIdx) = "WNT";}
        else if(gSharePred == "WNT"){gShareTbl.at(gShareIdx) = "WT";}
        else if(gSharePred == "WT"){gShareTbl.at(gShareIdx) = "ST";}       
  }
//SELECTOR
    //if our selector was on gShare and gshare was correct, correct ++ and vice versa for bimod
    if( (selectorTbl.at(index) == "SG" || selectorTbl.at(index) == "WG") && gShareCorrect == 1){correct++;}
    else if( (selectorTbl.at(index) == "SB" || selectorTbl.at(index) == "WB") && bimodCorrect == 1){correct++;}
    //if outcomes were the same for both bimodal and gshare, reset selector to initial prediction
    if(bimodCorrect == gShareCorrect) { selectorTbl.at(index) = equalpred; }
    //else, if bimod was correct and g was incorrect
    else if(bimodCorrect == 1 && gShareCorrect == 0){
      //we move towards bimodal
      if(selectorTbl.at(index) == "SG"){ selectorTbl.at(index) = "WG";}
      else if(selectorTbl.at(index) == "WG"){selectorTbl.at(index) = "WB";}
      else if(selectorTbl.at(index) == "WB"){selectorTbl.at(index) = "SB";}  
    }
    else if(bimodCorrect == 0 && gShareCorrect == 1){
      //we move towards gShare
      if(selectorTbl.at(index) == "SB"){ selectorTbl.at(index) = "WB";}
      else if(selectorTbl.at(index) == "WB"){selectorTbl.at(index) = "WG";}
      else if(selectorTbl.at(index) == "WG"){selectorTbl.at(index) = "SG";}  
    }

    //now we want to shift ghr to the left
      //go through the ghr vector +1 because were tossing the oldest bit
      for(i=1; i<ghr11.size(); i++){
          ghr11.at(i-1) = ghr11.at(i);
        }
      //now if ghr behavior was T, set 
      if(behavior == "T"){
        ghr11.at(ghr11.size()-1) = 1;
      }
      else{ 
        ghr11.at(ghr11.size()-1) = 0;
      }
  }
  fout << correct << "," << total << ";";
  fout <<endl;
  infile.close();
  infile.open(file);   
}
int main(int argc, char *argv[]) {
  if(argc != 3) {
    cout<<"input error" << endl;
    return 1;
  }

  string inputFile = argv[1];
  string output = argv[2];

  std::ofstream fout(output);
  
  alwaystaken(inputFile, fout);
  alwaysnontaken(inputFile, fout);
  singlebit(inputFile, fout);
  twobit(inputFile, fout);
  gshare(inputFile, fout);
  tournament(inputFile, fout);

  fout.close();
}