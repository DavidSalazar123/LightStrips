// Constants for methods
#define FASTLED_INTERNAL
#include <FastLED.h>
#define NUMLED 157 // How many dots are on our strip?
#define DATAPIN 6  // Pin on Arduino that connects with lights
#define ACTIVATED LOW
CRGB LED[NUMLED]; // List for dots on strip (elements)

uint8_t hue = 0;       // Unsined Byte for rainbow
const byte SWITCH = 2; // Pin on arduino for SWITCH input
byte switchState = 0;
int list[NUMLED];
int randhue = random(25, 256);
int inverthue = (randhue + 180) % 360;

/* Useful information
 *
 * beatsin8(bpm, lowVal, highVal, timeBase,phaseOffset)
 *      It is used to show a "wave" going up and down
 *      lowwest val = 0
 *      highest val = 300 or NUMLED
 *      For more precision, use floating numbers
 *      phaseOffset = moves starting pobyte of wave forward
 *      timeBase = moves starting pobyte of wave forward
 *        Only use one of phaseOffset or timeBase
 *
 *CRGB Object
 *
 *LED[i] = CRGB(r, g, b) or LED[i].setRGB(r,g,b)
 *    Setting the color of LED dot to rgb
 *
 *LED[i].r = hevalue number
 *    Setting the r or g or b independently to certain dotLED
 *
 *LED[o]=LED[1];
 *    Coping the color of one LED to another
 *
 * fill_solid(LED,NUMLED,CRGB(R,G,B));
 *    listayLED, 0 to what number in listayLED is solid, what color
 *
 *CHSV Object
 **The increase in hue is the rainbow
 * HSV = Hue, Saturation, and Value/Brightness
 * Values of 0-255
 *
 * LED[i]= CHSV(hue, saturation, value);
 *      It is like RGB
 *
 * LED[i].h = value
 *      Setting the h or s or v independently ti a certaub dotLED
 *
 *
 *
 *
 */
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// LED Methods
/*
 * Sorting methods
 */
void setup()
{
  FastLED.addLeds<WS2811, DATAPIN>(LED, NUMLED); // Tells library that the lightStrip(WS2811) on DATAPIN will use data from listay List
  FastLED.setBrightness(100);                    // Help travel to all of led strips

  // SWITCH set up
  pinMode(SWITCH, INPUT); // Take inputs from SWITCH
  Serial.begin(9600);
  digitalWrite(SWITCH, HIGH); // Take SWITCH as input
}

void pacMan(byte iterations)
{
  byte oldIteration = iterations;

  while (iterations < (oldIteration * 2))
  {
    for (byte i = 0; i < NUMLED; i++)
    {
      fill_solid(LED, NUMLED, CHSV(234, 255, 255));
      FastLED.show();

      LED[i] = CHSV(60, 255, 255); // Pac Man
      FastLED.show();

      // The Ghosts
      LED[i + 5] = CHSV(0, 0, 255);
      LED[i + 10] = CHSV(30, 255, 255);
      LED[i + 15] = CHSV(160, 255, 255);
      LED[i + 20] = CHSV(200, 255, 255);
      FastLED.show();

      delay(100);
      LED[i] = CRGB::Black;
    }
    iterations++;
  }
}

void brightLights() // All white lights
{
  fill_solid(LED, NUMLED, CHSV(0, 0, 255));
  FastLED.show();
}

void pulsingLights(byte iterations) // On and off lights slowing fading
{
  byte oldIteration = iterations;

  while (iterations < (oldIteration * 2))
  {

    // Fade in lights
    short hue = random(0, 360);

    for (short j = 50; j < 200; j++)
    {
      fill_solid(LED, NUMLED, CHSV(hue, 255, j));
      FastLED.show();
      delay(5);
    }

    // Fading out lights
    for (short i = 25; i < 50; i++)
    {
      fadeToBlackBy(LED, NUMLED, i);
      delay(10);
      FastLED.show();
    }

    iterations++;
  }
}

void rainbowFill(byte iterations) // Rotation of rainbows
{
  byte oldIteration = iterations;

  while (iterations < (oldIteration * 2))
  {
    uint16_t beatA = beatsin16(30, 0, 255);
    uint16_t beatB = beatsin16(20, 0, 255);
    fill_rainbow(LED, NUMLED, (beatA + beatB) / 2, 8);

    FastLED.show();

    iterations++;
  }
}

void racingLights(byte iterations)
{
  byte oldIteration = iterations;

  while (iterations < (oldIteration * 2))
  {

    short hue = random(0, 360);
    for (short j = 0; j < 20; j++)
    {
      fadeToBlackBy(LED, NUMLED, 20);
      byte pos = beatsin16(13, 0, NUMLED);
      LED[pos] += CHSV(hue, 255, 255);
      FastLED.show();
    }

    iterations++; // Increase loop
  }
}

void flashingLights(byte iterations) // Flash whole strip of LED on and off
{
  byte oldIteration = iterations;

  while (iterations < (oldIteration * 2))
  {
    // Random number from 0 - 255 for hevalue for dots
    short hue = random(0, 360);

    fill_solid(LED, NUMLED, CHSV(hue, 255, 255)); // listayLED, 0 to what number in listayLED is solid, what color
    FastLED.show();
    delay(500);

    fill_solid(LED, NUMLED, CRGB::Black);
    FastLED.show();
    delay(500);

    iterations++; // Increase loop
  }
}

void speedingLight(byte iterations) // Bounce the light from start of LED strip to end of LED strip
{
  byte oldIteration = iterations;

  while (iterations < (oldIteration * 2))
  {
    // Const Random number from 0 - 255 for hevalue for dots
    short hue = random(0, 360);

    for (byte i = 0; i < NUMLED; i++) // Go until the end of the LED Strip
    {
      LED[i] = CHSV(hue, 255, 255);
      LED[i + 1] = CHSV(hue, 255, 255);
      LED[i + 3] = CHSV(hue, 255, 255);
      LED[i + 4] = CHSV(hue, 255, 255);
      LED[i + 5] = CHSV(hue, 255, 255);
      FastLED.show();
      delay(10);
      LED[i] = CRGB::Black;
    }

    for (byte i = NUMLED - 1; i >= 0; i--) // Move Backwards when at the end of the LED Strip
    {
      LED[i] = CHSV(hue, 255, 255);
      LED[i + 1] = CHSV(hue, 255, 255);
      LED[i + 2] = CHSV(hue, 255, 255);
      LED[i + 3] = CHSV(hue, 255, 255);
      LED[i + 4] = CHSV(hue, 255, 255);
      LED[i + 5] = CHSV(hue, 255, 255);
      FastLED.show();
      delay(10);
      LED[i] = CRGB::Black;
      LED[i + 1] = CRGB::Black;
      LED[i + 2] = CRGB::Black;
      FastLED.show();
    }

    iterations++; // Increase loop
  }
}

void blinkingLights(byte iterations) // Blinking lights moving
{
  byte oldIteration = iterations;

  while (iterations < (oldIteration * 2))
  {
    // Const Random number from 0 - 255 for hevalue in first dot
    short hue = random(0, 360);

    for (byte ledDot = 0; ledDot < NUMLED; ledDot++)
    {
      for (byte loopFive = 0; loopFive < 5; loopFive++) // Makes the light blink 5 times
      {
        // Show dot of color
        LED[ledDot] = CHSV(hue, 255, 255);
        FastLED.show();
        delay(15);

        // Turn off dot
        LED[ledDot] = CRGB::Black;
        FastLED.show();
        delay(15);
      }
      LED[ledDot] = CHSV(hue, 255, 255);
      FastLED.show();
    }

    iterations++; // Increase loop
  }
}

void randomLine(byte iterations) // A line of color going to the end of the strip
{

  byte oldIteration = iterations;

  while (iterations < (oldIteration * 2))
  {
    // Random number from 0 - 255 for hevalue in first dot
    short hue = random(0, 360);

    for (short firstLine = 0; firstLine < NUMLED; firstLine++)
    {
      // firstline color
      LED[firstLine] = CHSV(hue, 255, 255);
      FastLED.show();
      delay(30);
    }

    iterations++; // Increase loop
  }
}

void christmasLights(byte iterations)
{
  byte oldIteration = iterations;

  while (iterations < (oldIteration * 2))
  {

    fill_solid(LED, NUMLED, CHSV(100, 255, 255)); // Green
    FastLED.show();
    delay(1000);

    fill_solid(LED, NUMLED, CHSV(0, 0, 255)); // White
    FastLED.show();
    delay(1000);

    fill_solid(LED, NUMLED, CHSV(0, 255, 255)); // Red
    FastLED.show();
    delay(1000);

    iterations++; // Increase loop
  }
}

void candyCane() // Creation of candy cane
{

  fill_solid(LED, NUMLED, CHSV(100, 255, 255)); // Red
  FastLED.show();

  for (byte i = 0; i < NUMLED; i++)
  {
    if (i % 2 == 0)
    {
      LED[i] = CHSV(0, 0, 255); // White
      FastLED.show();
      delay(100);
    }
  }
}

void oddEvenLines(byte iterations)
{
  byte oldIteration = iterations;

  while (iterations < (oldIteration * 2))
  {
    short hue = random(0, 360);

    for (byte i = 0; i < NUMLED; i++)
    {
      if (i % 2 == 0)
      {
        LED[i] = CHSV(hue, 255, 255); // White
        FastLED.show();
        delay(100);
      }
      else
      {
        LED[i] = CHSV(hue * 100, 255, 255); // White
        FastLED.show();
        delay(100);
      }
    }

    iterations++;
  }
}

//*Sorting algorithms*
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void newhue()
{
  randhue = random(25, 256);
  inverthue = (randhue + 180) % 360;
}

void randomList()
{
  newhue(); // Gets a new hue

  for (int i = 0; i < NUMLED; i++)
  {
    int randbrightness = random(256);
    LED[i] = CHSV(randhue, 255, randbrightness);
    list[i] = randbrightness;
  }

  FastLED.show();
}

void swap(int listay[], int a, int b)
{
  // SWAP
  int temp = listay[a];
  LED[a] = CHSV(inverthue, 255, 255);
  FastLED.show();

  listay[a] = listay[b];
  LED[b] = CHSV(inverthue, 255, 255);
  FastLED.show();

  LED[a] = CHSV(randhue, 255, list[b]); // LED Show
  FastLED.show();

  listay[b] = temp;
  LED[b] = CHSV(randhue, 255, temp); // LED Show
  FastLED.show();
}

//--------------------------------------------------------------------------------------------------------
void bubbleSort()
{
  for (int i = 0; i < NUMLED; i++)
  {
    for (int j = i + 1; j < NUMLED; j++)
    {
      if (list[j] < list[i])
      {
        swap(list, i, j);
      }
    }
  }
}

//-----------------------------------------------------------------------------------------------------

void selectionSort()
{
  for (int i = 0; i < (NUMLED - 1); i++)
  {
    int minindevalue = i;
    for (int j = i + 1; j < NUMLED; j++)
    {
      if (list[j] < list[minindevalue])
      {
        minindevalue = j;
      }

      swap(list, minindevalue, i);
    }
  }
}

//-----------------------------------------------------------------------------------------------------

void insertionSort()
{
  for (int i = 1; i < NUMLED; i++)
  {
    int key = list[i];
    int j = i - 1;

    while (j >= 0 && list[j] > key)
    {
      list[j + 1] = list[j];
      LED[j + 1] = CHSV(inverthue, 255, 255); // LED Show
      FastLED.show();

      LED[j + 1] = CHSV(randhue, 255, list[j]); // LED Show
      FastLED.show();
      --j;
    }

    list[j + 1] = key;
    LED[j + 1] = CHSV(randhue, 255, key); // LED Show
    FastLED.show();
  }
}

//-----------------------------------------------------------------------------------------------------
void shellSort()
{
  for (int interval = NUMLED / 2; interval > 0; interval /= 2)
  {
    for (int i = interval; i < NUMLED; i++)
    {
      int temp = list[i];
      int j;
      for (j = i; j >= interval && list[j - interval] > temp; j -= interval)
      {
        list[j] = list[j - interval];
        LED[j] = CHSV(inverthue, 255, 255); // LED Show
        FastLED.show();

        LED[j] = CHSV(randhue, 255, list[j - interval]); // LED Show
        FastLED.show();
      }

      list[j] = temp;
      LED[j] = CHSV(inverthue, 255, 255); // LED Show
      FastLED.show();

      LED[j] = CHSV(randhue, 255, temp); // LED Show
      FastLED.show();
    }
  }
}
//-----------------------------------------------------------------------------------------------------
void radivalueSort()
{
  int i;
  int mavaluenum = 3; // decimal numbers
  int output[NUMLED];
  int p = 1;
  int indevalue, temp, count = 0;
  for (int i = 0; i < mavaluenum; i++)
  {
    int m = pow(10, i + 1);
    int p = pow(10, i);

    for (int j = 0; j < NUMLED; j++)
    {
      temp = list[j] % m;
      indevalue = temp / p; // find indevalue for pocket listay
      output[indevalue + 1] = list[j];
    }
  }
}

//-----------------------------------------------------------------------------------------------------
void merge(int l, int m, int r)
{
  int i, j, k, nl, nr;
  nl = m - l + 1;
  nr = r - m;
  int llist[nl], rlist[nr];

  // Sort left listay
  for (i = 0; i < nl; i++)
  {
    llist[i] = list[l + i];
    LED[i] = CHSV(inverthue, 255, 255); // LED Show
    FastLED.show();

    LED[i] = CHSV(randhue, 255, list[l + i]); // LED Show
    FastLED.show();
  }

  // Sort right listay
  for (j = 0; j < nr; j++)
  {
    rlist[j] = list[m + 1 + j];

    LED[j] = CHSV(inverthue, 255, 255); // LED Show
    FastLED.show();

    LED[j] = CHSV(randhue, 255, list[m + 1 + j]); // LED Show
    FastLED.show();
  }

  i = 0;
  j = 0;
  k = l;

  while (i < nl && j < nr)
  {
    if (llist[i] <= rlist[j])
    {
      list[k] = llist[i];
      LED[k] = CHSV(inverthue, 255, 255); // LED Show
      FastLED.show();

      LED[k] = CHSV(randhue, 255, llist[i]); // LED Show
      FastLED.show();
      i++;
    }
    else
    {
      list[k] = rlist[j];

      LED[k] = CHSV(inverthue, 255, 255); // LED Show
      FastLED.show();

      LED[k] = CHSV(randhue, 255, rlist[j]); // LED Show
      FastLED.show();
      j++;
    }

    k++;
  }

  while (i < nl)
  {
    list[k] = llist[i];
    LED[k] = CHSV(randhue, 255, llist[i]); // LED Show
    FastLED.show();
    i++;
    k++;
  }

  while (j < nr)
  {
    list[k] = rlist[j];
    LED[k] = CHSV(randhue, 255, rlist[j]); // LED Show
    FastLED.show();
    j++;
    k++;
  }
}

void mergeSort(int l, int r)
{
  if (l < r)
  {
    int m = l + (r - l) / 2;
    mergeSort(l, m);
    mergeSort(m + 1, r);
    merge(l, m, r);
  }
}
//-----------------------------------------------------------------------------------------------------
int partition(int listay[], int low, int high)
{
  int pivot = listay[high];
  LED[high] = CHSV(0, 0, 255); // LED Show
  FastLED.show();

  int i = (low - 1);

  for (int j = low; j < high; j++)
  {
    if (listay[j] <= pivot)
    {
      i++;
      swap(listay, i, j);
    }
  }

  swap(listay, i + 1, high);
  return (i + 1);
}

// Random selection of pivot.
int randomPivotSelection(int listay[], int low, int high)
{
  int n = rand();
  // Randomizing the pivot value in the given subpart of listay.
  int pivot = low + n % (high - low + 1);

  swap(listay, high, pivot);
  return partition(listay, low, high);
}

int median3(int listay[], int left, int right)
{
  int mid = right / 2;

  // Sort values
  if (listay[left] > listay[mid])
    swap(listay, left, mid);

  if (listay[left] > listay[right])
    swap(listay, left, right);

  if (listay[mid] > listay[right])
    swap(listay, mid, right);

  swap(listay, mid, right);
  return partition(listay, left, right);
}

void quickSort_median3(int listay[], int low, int high)
{
  if (low < high)
  {
    int pivot = median3(listay, low, high);

    quickSort(listay, low, high);
  }
}

void quickSort_random(int listay[], int low, int high)
{
  if (low < high)
  {
    int pivot = randomPivotSelection(listay, low, high);

    // recursive call on the left of pivot
    quickSort_random(listay, low, pivot - 1);

    // recursive call on the right of pivot
    quickSort_random(listay, pivot + 1, high);
  }
}

void quickSort(int listay[], int low, int high)
{
  if (low < high)
  {
    int pivot = partition(listay, low, high);

    // recursive call on the left of pivot
    quickSort(listay, low, pivot - 1);

    // recursive call on the right of pivot
    quickSort(listay, pivot + 1, high);
  }
}

//-----------------------------------------------------------------------------------------------------
void timSort()
{
  const int RUN = 64;
  for (int i = 0; i < NUMLED; i += RUN)
  {
    int left = i;
    int right = min((i + RUN - 1), (NUMLED - 1));
    // Insertion Sort
    for (int i = left + 1; i <= right; i++)
    {
      int temp = list[i];
      int j = i - 1;
      while (j >= left && list[j] > temp)
      {
        list[j + 1] = list[j];
        j--;
      }

      list[j + 1] = temp;
    }
  }

  // Start merging from size RUN (or 32).
  // It will merge
  // to form size 64, then 128, 256
  // and so on ....
  for (int size = RUN; size < NUMLED; size = 2 * size)
  {

    // pick starting point of
    // left sub listay. We
    // are going to merge
    // list[left..left+size-1]
    // and list[left+size, left+2*size-1]
    // After every merge, we
    // increase left by 2*size
    for (int left = 0; left < NUMLED; left += 2 * size)
    {

      // find ending point of
      // left sub listay
      // mid+1 is starting point
      // of right sub listay
      int mid = left + size - 1;
      int right = min((left + 2 * size - 1), (NUMLED - 1));

      // merge sub listay list[left.....mid] &
      // list[mid+1....right]
      if (mid < right)
        merge(left, mid, right);
    }
  }
}
//-----------------------------------------------------------------------------------------------------
void heapify(int list[], int n, int i)
{
  int largest = i;   // Initialize largest as root
  int l = 2 * i + 1; // left = 2*i + 1
  int r = 2 * i + 2; // right = 2*i + 2

  // If left child is larger than root
  if (l < n && list[l] > list[largest])
    largest = l;

  // If right child is larger than largest so far
  if (r < n && list[r] > list[largest])
    largest = r;

  // If largest is not root
  if (largest != i)
  {
    swap(list, i, largest);
    // Recursively heapify the affected sub-tree
    heapify(list, n, largest);
  }
}

void heapSort()
{
  // Build heap (relistange listay)
  for (int i = NUMLED / 2 - 1; i >= 0; i--)
    heapify(list, NUMLED, i);

  // One by one evaluetract an element from heap
  for (int i = NUMLED - 1; i > 0; i--)
  {
    // Move current root to end
    swap(list, 0, i);

    // call mavalue heapify on the reduced heap
    heapify(list, i, 0);
  }
}
//-----------------------------------------------------------------------------------------------------
//*Searching algorithms*
void linearSearch()
{
  int indevalue = random(70, NUMLED);
  int value = list[indevalue];
  int i = 0;
  LED[indevalue] = CHSV(0, 0, 255); // LED Show
  FastLED.show();

  for (i = 0; i < NUMLED; i++)
  {
    LED[i - 1] = CHSV(randhue, 255, list[i - 1]); // LED Show
    FastLED.show();

    if (list[i] == value)
    {
      LED[i] = CHSV(randhue, 255, list[i]); // LED Show
      FastLED.show();
      break;
    }
    else
    {
      LED[i] = CHSV(inverthue, 255, 255); // LED Show
      FastLED.show();
    }
  }

  delay(2000);
  LED[i] = CHSV(randhue, 255, list[i]);
  FastLED.show();
}
//-----------------------------------------------------------------------------------------------------
void binarySearch()
{
  int indevaluevalue = random(70, NUMLED);
  int value = list[indevaluevalue];
  int last = NUMLED - 1;
  int start = 0;

  LED[indevaluevalue] = CHSV(0, 0, 255); // LED Show
  LED[last] = CHSV(100, 255, 255);       // LED Show
  LED[start] = CHSV(100, 255, 255);      // LED Show
  FastLED.show();

  while (start <= last)
  {
    int mid = (start + last) / 2;
    LED[mid] = CHSV(inverthue, 255, 255); // LED Show
    FastLED.show();
    delay(1000);

    if (list[mid] > value)
    {
      int prev = last;
      LED[last] = CHSV(100, 255, 255); // LED Show
      FastLED.show();
      last = mid - 1;
      LED[last] = CHSV(100, 255, 255);            // LED Show
      LED[prev] = CHSV(randhue, 255, list[prev]); // LED Show
      FastLED.show();
    }
    else if (list[mid] < value)
    {
      int prev = start;
      LED[start] = CHSV(100, 255, 255); // LED Show
      FastLED.show();

      start = mid + 1;
      LED[start] = CHSV(100, 255, 255);     // LED Show
      LED[prev] = CHSV(randhue, 255, prev); // LED Show
      FastLED.show();
    }
    else
      break;

    LED[mid] = CHSV(randhue, 255, list[mid]); // LED Show
    FastLED.show();
  }
}
//-----------------------------------------------------------------------------------------------------
void jumpSearch()
{
  int step = sqrt(NUMLED);
  int indevaluevalue = random(70, NUMLED);
  int value = list[indevaluevalue];
  LED[indevaluevalue] = CHSV(0, 0, 255); // LED Show
  FastLED.show();
  int prev = 0;

  while (list[min(step, NUMLED) - 1] < value)
  {
    prev = step;
    LED[prev] = CHSV(inverthue, 255, 255); // LED Show
    FastLED.show();
    step += sqrt(NUMLED);

    delay(1000);
    LED[prev] = CHSV(randhue, 255, list[prev]); // LED Show
    FastLED.show();
  }

  while (list[prev] < value)
  {
    prev++;
    LED[prev] = CHSV(inverthue, 255, 255); // LED Show
    FastLED.show();
    delay(1000);
    LED[prev] = CHSV(randhue, 255, list[prev]); // LED Show
    FastLED.show();
  }
}
//-----------------------------------------------------------------------------------------------------
void interpolationSearch()
{
  // Find indevaluees of two corners
  int low = 0;
  int high = (NUMLED - 1);
  int indevaluevalue = random(70, NUMLED);
  int value = list[indevaluevalue];
  LED[indevaluevalue] = CHSV(0, 0, 255); // LED Show
  FastLED.show();

  // Since listay is sorted, an element present
  // in listay must be in range defined by corner
  while (low <= high && value >= list[low] && value <= list[high])
  {
    int position = low + (((double)(high - low) / (list[high] - list[low])) * (value - list[low]));

    LED[position] = CHSV(inverthue, 255, 255);
    FastLED.show();
    delay(2000);

    // Condition of target found
    if (list[position] == value)
      break;

    if (list[position] < value)
      low = position + 1;
    else
      high = position - 1;

    LED[position] = CHSV(randhue, 255, list[position]);
    FastLED.show();
  }
}

//-----------------------------------------------------------------------------------------------------
int fibSearch()
{
  int indexvalue = random(70, NUMLED);
  int value = list[indexvalue];
  LED[indexvalue] = CHSV(0, 0, 255); // LED Show
  FastLED.show();

  /* Initialize fibonacci numbers */
  int fib2 = 0;           // (m-2)'th Fibonacci No.
  int fib1 = 1;           // (m-1)'th Fibonacci No.
  int fibM = fib2 + fib1; // m'th Fibonacci

  /* fibM is going to store the smallest Fibonacci
     Number greater than or equal to n */
  while (fibM < NUMLED)
  {
    fib2 = fib1;
    fib1 = fibM;
    fibM = fib2 + fib1;
  }

  // Marks the eliminated range from front
  int offset = -1;

  /* while there are elements to be inspected. Note that
     we compare list[fibMm2] with value. When fibM becomes 1,
     fibMm2 becomes 0 */
  while (fibM > 1)
  {
    // Check if fibMm2 is a valid location
    int i = min(offset + fib2, NUMLED - 1);
    LED[i] = CHSV(inverthue, 255, 255);
    FastLED.show();

    delay(1000);
    /* If value is greater than the value at indevalue fibMm2,
       cut the sublistay listay from offset to i */
    if (list[i] < value)
    {
      fibM = fib1;
      fib1 = fib2;
      fib2 = fibM - fib1;
      offset = i;
    }
    /* If value is greater than the value at indevalue fibMm2,
       cut the sublistay after i+1  */
    else if (list[i] > value)
    {
      fibM = fib2;
      fib1 = fib1 - fib2;
      fib2 = fibM - fib1;
    }
    else // Value found
    {
      LED[i] = CHSV(randhue, 255, list[i]);
      FastLED.show();
      break;
    }

    LED[i] = CHSV(randhue, 255, list[i]);
    FastLED.show();
  }

  /* comparing the last element with value */
  if (fib1 && list[offset + 1] == value)
  {
    LED[offset + 1] = CHSV(inverthue, 255, 255);
    FastLED.show();
  }
}
//-----------------------------------------------------------------------------------------------------

// Main Method
void loop()
{
  // Sorting Algorithms *Inorder: Worst to Best
  randomList(); // Reset list for new sorting
  bubbleSort();
  randomList();
  selectionSort();
  randomList();
  insertionSort();
  randomList();
  shellSort();
  randomList();
  quickSort(list, 0, NUMLED - 1);
  randomList();
  quickSort_random(list, 0, NUMLED - 1);
  randomList();
  quickSort_median3(list, 0, NUMLED - 1);
  randomList();
  mergeSort(0, NUMLED - 1);
  randomList(); // Reset list for new sorting
  heapSort();
  randomList(); // Reset list for new sorting
  timSort();

  // Sorting Algorithms
  linearSearch();
  interpolationSearch();
  fibSearch();
  jumpSearch();
  binarySearch();

  // Cool Designs
  racingLights(500);
  christmasLights(50);
  flashingLights(50);
  randomLine(50);
  blinkingLights(50);
  pulsingLights(50);
  pacMan(30);

  // Need Work
  // oddEvenLines(5);
  // candyCane();
  // rainbowFill(500);
}
