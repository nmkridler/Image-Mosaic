#include <surf.h>

Surf::Surf( cv::Mat const & refImg, cv::Mat const & newImg, double const & hThresh) :
Register(),
m_hThresh(hThresh)
{
   // Convert the images to grayscale
   cvtColor(refImg, m_refGray, CV_RGB2GRAY);
   cvtColor(newImg, m_newGray, CV_RGB2GRAY);

   // Create the detector
   m_detector.reset( new cv::SurfFeatureDetector(m_hThresh) );
}

void Surf::calculateHomography()
{
   // Create vectors of key points
   std::vector<cv::KeyPoint> refKeyPts;
   std::vector<cv::KeyPoint> newKeyPts;

   // Detect the key points
   m_detector->detect(m_refGray,refKeyPts);
   m_detector->detect(m_newGray,newKeyPts);

   // Compute the descriptors
   cv::Mat refDescrip;
   cv::Mat newDescrip;
   m_extractor.compute(m_refGray,refKeyPts,refDescrip);
   m_extractor.compute(m_newGray,newKeyPts,newDescrip);

   // Match the descriptors
   std::vector<cv::DMatch> matches;
   m_matcher.match(refDescrip,newDescrip,matches);

   std::vector<cv::Point2f> trainPts;
   std::vector<cv::Point2f> queryPts;
   for( size_t idx = 0; idx < matches.size(); ++idx)
   {
      const cv::DMatch& match = matches[idx];
      queryPts.push_back(refKeyPts[match.queryIdx].pt);
      trainPts.push_back(newKeyPts[match.trainIdx].pt);
   }
 
   // Calculate the homography
   m_homog = cv::findHomography(cv::Mat(trainPts),cv::Mat(queryPts),cv::RANSAC,9);

}
