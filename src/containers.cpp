#include <iostream>
#include <unistd.h>
#include <ctime>
#include <vector>
#include <list>
#include <queue>


#include <CommonVals.h>


using std::cout;
using std::endl;



void printHeader() {
   cout << endl;
   cout << "===============================================" << endl;
   cout << "My own experiments with containers" << endl;
   cout << "===============================================" << endl;
   cout << endl;
}

struct DatagramData {
   unsigned int index;
   std::vector<unsigned char > datagram;
};

const unsigned int  NUMBER_OF_TESTS = 1000000;

template <typename T>
void performTest( T & containterToTest, const unsigned int numberOfTests,
                  const bool emplaceBackFlag ) {
   if (emplaceBackFlag) {
      cout << "performTest >>> elements will be inserted with emplace_back method " << endl;
   }
   else {
      cout << "performTest >>> elements will be inserted with push_back method " << endl;
   }
   DatagramData datagramData = { 0, {0x01, 0x02, 0x03}};
   clock_t startPoint = clock();
   for ( unsigned int i = 1; i < numberOfTests + 1; ++ i) {
      //cout << "Loop number " << i << ":" << endl;
      datagramData.index = i;
      if ( emplaceBackFlag ) {
         containterToTest.emplace_back( datagramData );
      }
      else {
         containterToTest.push_back( datagramData );
      }
      for ( auto pos = containterToTest.begin(); pos != containterToTest.end(); ++ pos ) {
         if ( pos->index == ( i - 1 ) ) {
            //cout << "Erasing datagram data with index " << pos->index << endl;
            containterToTest.erase( pos );
            break;
         }
      }
   }
   clock_t finishPoint = clock();
   float duration = static_cast<float>( finishPoint - startPoint ) / CLOCKS_PER_SEC;
   cout << "performTest >>> duration of the " << numberOfTests << " tests: " << duration << " second(s)" << endl;
}

/*
template <>
void performTest<std::list<DatagramData>>( std::list<DatagramData> & containterToTest, const unsigned int numberOfTests,
                                           const bool emplaceBackFlag ) {
   if (emplaceBackFlag) {
      cout << "performTest<std::list<DatagramData>> >>> elements will be inserted with emplace_back method " << endl;
   }
   else {
      cout << "performTest<std::list<DatagramData>> >>> elements will be inserted with push_back method " << endl;
   }
   DatagramData datagramData = { 0, {0x01, 0x02, 0x03}};
   clock_t startPoint = clock();
   for ( unsigned int i = 1; i < numberOfTests + 1; ++ i) {
      //cout << "Loop number " << i << ":" << endl;
      datagramData.index = i;
      if ( emplaceBackFlag ) {
         containterToTest.emplace_back( datagramData );
      }
      else {
         containterToTest.push_back( datagramData );
      }
      for ( auto pos = containterToTest.begin(); pos != containterToTest.end(); ) {
         if ( pos->index == ( i - 1 ) ) {
            //cout << "Erasing datagram data with index " << pos->index << endl;
            //pos = datagramDataListPB.erase( pos );
            containterToTest.erase( pos );
            break;
         }
         else {
            ++ pos;
         }
      }
   }
   clock_t finishPoint = clock();
   float duration = static_cast<float>( finishPoint - startPoint ) / CLOCKS_PER_SEC;
   cout << "performTest<std::list<DatagramData>> >>> duration of the " << numberOfTests << " tests: " << duration
        << " second(s)" << endl;
}
*/

int main( int argc, char *argv[] ) {
   printHeader();

   cout << "argc = " << argc << endl;

   unsigned int numOfTests = NUMBER_OF_TESTS;
   if ( argc == 2 ) {
      numOfTests = static_cast<unsigned int>( atoi( argv[1] ) );
   }

   cout << endl;
   cout << "Testing std::deque with push_back..." << endl;
   std::deque<DatagramData> datagramDataDequePB;
   performTest( datagramDataDequePB, numOfTests, false );

   cout << endl;
   cout << "Testing std::deque with emplace_back..." << endl;
   std::deque<DatagramData> datagramDataDequeEB;
   performTest( datagramDataDequeEB, numOfTests, true );

   cout << endl;
   cout << "Testing std::list with push_back..." << endl;
   std::list<DatagramData> datagramDataListPB;
   performTest( datagramDataListPB, numOfTests, false );

   cout << endl;
   cout << "Testing std::list with emplace_back..." << endl;
   std::list<DatagramData> datagramDataListEB;
   performTest( datagramDataListEB, numOfTests, true );

   cout << endl;
   cout << "Testing std::vector with push_back..." << endl;
   std::vector<DatagramData> datagramDataVectorPB;
   performTest( datagramDataVectorPB, numOfTests, false );

   cout << endl;
   cout << "Testing std::vector with emplace_back..." << endl;
   std::vector<DatagramData> datagramDataVectorEB;
   performTest( datagramDataVectorEB, numOfTests, true );

   cout << endl;

   return 0;
}
