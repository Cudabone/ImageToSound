#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>
#include <cmath>
/*TODO
 * 1. Get a base image to process
 * 2. Decide the resolution per frequency (pixels)
 * 		-Consist of a few rows and columns likely
 * 3. Determine the frequency range per each block
 * 4. Write the converter function
 * 5. Figure out compiler issues
 */
/*
 * Sounds combine by adding sine waves
 * Create and play a single sine wave which is the 
 * addition of all sine waves which should play per column.
 * Qt library is one option
 */
bool process_image(const cv::Mat &image);
void play_cols(int **sounds, int width, int height);
int avg_brightness(const cv::Mat &image);

int main(int argc, char **argv)
{
	std::string file = "filename";
	if(argc != 2)
	{
		std::cout << "Usage: ./imgtosound <filename>" << std::endl;
		return -1;
	}

	//Load in image and convert to grayscale
	//This is done for detecting objects on brightness
	cv::Mat image = cv::imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);

	if(!image.data)
	{
		std::cout << "Could not open or find file: " << file << std::endl;
		return -1;
	}
	/*
	cv::namedWindow( "Display window ", cv::WINDOW_AUTOSIZE);
	cv::imshow( "Display window ", image);
	cv::waitKey(0);
	return 0;
	*/
	if(!process_image(image))
		return -1;

}
/* Process_Image obtains the image's brightness value into a 2-D array
 * of frequency values if the brightness value is greater than the 
 * threshold. This threshold can be based upon the average brightness
 * values if desired
 */
bool process_image(const cv::Mat &image)
{
	//TODO create a 2-D vector based on resolution of sound output
	//Ex: divide into 16 segments, 3 rows and columns of pixels each
	//std::vector sound_col; 	

	int width = image.cols;
	int height = image.rows;
	int sounds[width][height];
	std::cout << "Width of image: " << width << std::endl;
	std::cout << "Height of image: " << height << std::endl;


	int x,y;

	//Initialize the sounds array to 0's 
	for(x = 0; x < width; x++)
		for(y = 0; y < height; y++)
			sounds[x][y] = 0;

	//Brightness threshold for sounds
	//TODO May base threshold on an average brightness and standard deviation
	//calculation such that it adapts to brighter and darker images well
	int threshold = avg_brightness(image);
	
	//>= 128 is halfway between black and white
	//int threshold = 128;
	
	//Frequency Range Desired ~ 2 - 5 KHz, hearing most sensitive to this
	//range
	//TODO change this range to desired sound range
	//3KHz / height, gives range per pixel
	float range_low = 2000.0;
	float range_high = 5000.0;
	float range = range_high - range_low;
	int division = ceil(range/(float)height);

	cv::Scalar pixel; //opencv value of pixel 0-255 255 == white, 0 == black

	//TODO do averaging based on stride, then compare to threshold
	for(x = 0; x < width; x++)
		for(y = 0; y < height; y++)
		{
			pixel = image.at<uchar>(y,x);
			if(y == 150)
				std::cout << "pixel " << " == " << pixel.val[0] << std::endl;
			//TODO assign sound value to play
			if(pixel.val[0] >= threshold)
			{
				sounds[x][y] = y*division + range_low; //Store frequency to play for pixel

				/* TODO assign frequency based on row
				case x:
				*/
			}
			else sounds[x][y] = 0;
		}
	//Play all of the columns
	/*
	play_cols((int **)sounds,width,height);
	*/
	//TODO play the image sounds based on columns, delay, and add a note after
	//one pass is completed.
	return 1;
}
/* TODO this function will output the sounds based upon the frequency value
 * for each pixel. The function will play each column of the image
 * consecutively and will play a sound to note it has reached the end of the
 * image. 
 * On OS X, Core Audio needs to be used for audio playback
 * On other platforms, another library will likely need to be used
 */
void play_cols(int **sounds, int width, int height)
{
	int x,y;
	for(x = 0; x < width; x++)
	{
		for(y = 0; y < height; y++)
		{
			
		}
		//TODO Wait here
	}
	//TODO Play sound after last column to signify done
}
/* Measures the average brightness value from an image and returns the 
 * value.
 */
int avg_brightness(const cv::Mat &image)
{
	cv::Scalar pixel;
	int width = image.cols;
	int height = image.rows;
	int total = width * height;
	int sum = 0;
	int x,y;
	std::cout << "Width of image: " << width << std::endl;
	std::cout << "Height of image: " << height << std::endl;
	for(x = 0; x < width; x++)
	{
		for(y = 0; y < height; y++)
		{
			pixel = image.at<uchar>(y,x);
			sum += pixel.val[0];
		}
	}
	int avg = ceil(sum/((float)total));
	std::cout << "Average pixel brightness: " << avg << std::endl;
	return avg;
}
