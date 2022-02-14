#include "TGA.h"
#include <iostream>

int test(int test_num, bool test) {
  std::cout << "Test #" << test_num << "....... ";
  if (test) {
    std::cout << "Passed!" << std::endl;
    return 1;
  } else {
    std::cout << "Failed." << std::endl;
    return 0;
  }
}

bool test_1() {
  // Basic setup
  char *file1 = (char *) "input/layer1.tga";
  char *file2 = (char *) "input/pattern1.tga";
  char *outfile = (char *) "output/part1.tga";
  char *outtest = (char *) "examples/EXAMPLE_part1.tga";

  TGA top(file1);
  TGA bottom(file2);
  TGA example(outtest);
  TGA output;

  // Desired transformation
  TGA::Multiply(top, bottom, output);
  output.write(outfile);

  // Equality check
  return (output == example);
}

bool test_2() {
  char *file1 = (char *) "input/layer2.tga";
  char *file2 = (char *) "input/car.tga";
  char *outfile = (char *) "output/part2.tga";
  char *outtest = (char *) "examples/EXAMPLE_part2.tga";

  TGA top(file1);
  TGA bottom(file2);
  TGA example(outtest);
  TGA output;

  TGA::Subtract(top, bottom, output);
  output.write(outfile);

  return (output == example);
}

bool test_3() {
  char *file1 = (char *) "input/layer1.tga";
  char *file2 = (char *) "input/pattern2.tga";
  char *file3 = (char *) "input/text.tga";
  char *outfile = (char *) "output/part3.tga";
  char *outtest = (char *) "examples/EXAMPLE_part3.tga";

  TGA top(file1);
  TGA bottom(file2);
  TGA text(file3);
  TGA example(outtest);
  TGA output;

  TGA::Multiply(top, bottom, output);
  TGA::Screen(text, output, output);
  output.write(outfile);

  return (output == example);
}

bool test_4() {
  char *file1 = (char *) "input/layer2.tga";
  char *file2 = (char *) "input/circles.tga";
  char *file3 = (char *) "input/pattern2.tga";
  char *outfile = (char *) "output/part4.tga";
  char *outtest = (char *) "examples/EXAMPLE_part4.tga";

  TGA top(file1);
  TGA bottom(file2);
  TGA pattern(file3);
  TGA example(outtest);
  TGA output;

  TGA::Multiply(top, bottom, output);
  TGA::Subtract(pattern, output, output);
  output.write(outfile);

  return (output == example);
}

bool test_5() {
  char *file1 = (char *) "input/layer1.tga";
  char *file2 = (char *) "input/pattern1.tga";
  char *outfile = (char *) "output/part5.tga";
  char *outtest = (char *) "examples/EXAMPLE_part5.tga";

  TGA top(file1);
  TGA bottom(file2);
  TGA example(outtest);
  TGA output;

  TGA::Overlay(top, bottom, output);
  output.write(outfile);

  return (output == example);
}

bool test_6() {
  char *file1 = (char *) "input/car.tga";
  int ADD = 200;
  char *outfile = (char *) "output/part6.tga";
  char *outtest = (char *) "examples/EXAMPLE_part6.tga";

  TGA top(file1);
  TGA example(outtest);
  TGA output;

  TGA::Add(top, GREEN, ADD, output);
  output.write(outfile);

  return (output == example);
}

bool test_7() {
  char *file1 = (char *) "input/car.tga";
  float REDSCALE = 4;
  float BLUESCALE = 0;
  char *outfile = (char *) "output/part7.tga";
  char *outtest = (char *) "examples/EXAMPLE_part7.tga";

  TGA top(file1);
  TGA example(outtest);
  TGA output;

  TGA::Scale(top, RED, REDSCALE, output);
  TGA::Scale(output, BLUE, BLUESCALE, output);
  output.write(outfile);

  return (output == example);
}

bool test_8() {
  char *file1 = (char *) "input/car.tga";
  char *outfile1 = (char *) "output/part8_b.tga";
  char *outfile2 = (char *) "output/part8_g.tga";
  char *outfile3 = (char *) "output/part8_r.tga";
  char *outtest1 = (char *) "examples/EXAMPLE_part8_b.tga";
  char *outtest2 = (char *) "examples/EXAMPLE_part8_g.tga";
  char *outtest3 = (char *) "examples/EXAMPLE_part8_r.tga";

  TGA top(file1);
  TGA example1(outtest1);
  TGA example2(outtest2);
  TGA example3(outtest3);
  TGA output1;
  TGA output2;
  TGA output3;

  TGA::toGrayscale(top, BLUE, output1);
  TGA::toGrayscale(top, GREEN, output2);
  TGA::toGrayscale(top, RED, output3);
  output1.write(outfile1);
  output2.write(outfile2);
  output3.write(outfile3);

  return (output1 == example1
	  && output2 == example2
	  && output3 == example3);
}

bool test_9() {
  char *file1 = (char *) "input/layer_blue.tga";
  char *file2 = (char *) "input/layer_green.tga";
  char *file3 = (char *) "input/layer_red.tga";
  char *outfile = (char *) "output/part9.tga";
  char *outtest = (char *) "examples/EXAMPLE_part9.tga";

  TGA blue(file1);
  TGA green(file2);
  TGA red(file3);
  TGA example(outtest);
  TGA output;

  TGA::fromGrayscale(blue, BLUE, output);
  TGA::fromGrayscale(green, GREEN, output);
  TGA::fromGrayscale(red, RED, output);
  output.write(outfile);

  return (output == example);
}

bool test_10() {
  char *file1 = (char *) "input/text2.tga";
  char *outfile = (char *) "output/part10.tga";
  char *outtest = (char *) "examples/EXAMPLE_part10.tga";

  TGA top(file1);
  TGA example(outtest);
  TGA output;

  TGA::Reverse(top, output);
  output.write(outfile);

  return (output == example);
}

bool extra() {
  char *file1 = (char *) "input/circles.tga";
  char *file2 = (char *) "input/car.tga";
  char *file3 = (char *) "input/text.tga";
  char *file4 = (char *) "input/pattern1.tga";
  char *outfile = (char *) "output/extracredit.tga";
  char *outtest = (char *) "examples/EXAMPLE_extraCredit.tga";

  TGA one(file1);
  TGA two(file2);
  TGA three(file3);
  TGA four(file4);
  TGA example(outtest);
  TGA output;

  TGA::EXTRACREDIT(one, two, three, four, output);
  output.write(outfile);
  
  return (output == example);
}
  
int main() {
  int count = 0;

  count += test(1, test_1());
  count += test(2, test_2());
  count += test(3, test_3());
  count += test(4, test_4());
  count += test(5, test_5());
  count += test(6, test_6());
  count += test(7, test_7());
  count += test(8, test_8());
  count += test(9, test_9());
  count += test(10, test_10());
  
  std::cout << "Test results: " << count << " / 10" << std::endl;

  if (extra()) {
    std::cout << "Extra credit complete." << std::endl;
  }
  
  return 0;
}
