// HeliumCollision.cc

#include "HeliumMath.h"
#include "HeliumCollision.h"

#include <math.h>

namespace Helium
{
   namespace Collision
   {
      // @constants
      constexpr const float EPSILON = 0.000001f;

      // @helper-functions
      template <typename T> 
      T min(T a, T b) 
      { 
         return a < b ? a : b; 
      }

      template <typename T> 
      T max(T a, T b) 
      { 
         return a > b ? a : b; 
      }

      template <typename T> 
      T clamp(T v, T a, T b) 
      { 
         return v < a ? a : v > b ? b : v; 
      }

      // TODO: PASS
      bool intersect(const Vector2 &point, const BoundingCircle &circle)
      {
		  Vector2 offset = point - circle.center_;
		  if (offset.length() < circle.radius_)
		  {
			  return true;
		  }
		  else return false;
      }

      bool intersect(const Vector2 &point, const AxisAlignedBoundingBox &aligned_box)
      {
		  float left = aligned_box.center_.x_ - aligned_box.half_.x_;
		  float right = aligned_box.center_.x_ + aligned_box.half_.x_;
		  float top = aligned_box.center_.y_ + aligned_box.half_.y_;
		  float bottom = aligned_box.center_.y_ - aligned_box.half_.y_;
		  if (left < point.x_ && right > point.x_ && top > point.y_ && bottom < point.y_)
		  {
			   return true; 
		  }
          else return false;
      }

      bool intersect(const LineSegment &segment, const BoundingCircle &circle)
      {
          Vector2 Segment_Vector = segment.end_ - segment.start_;
          Vector2 Unit_Vector = Segment_Vector.unit();
          float Distance = Unit_Vector.dot(circle.center_ - segment.start_);
          Vector2 Closest_Point;
          if (Distance <= 0)
          {
              Closest_Point = segment.start_;
          }
          else if (Distance >= Segment_Vector.length())
          {
              Closest_Point = segment.end_;
          }
          else
          {
              Closest_Point = segment.start_ + Unit_Vector.operator*(Distance);
          }

          Vector2 Offset = Closest_Point - circle.center_;

          if (Offset.length() <= circle.radius_)
          {
              return true;
          }
          else
          {
              return false;
          }
      }

      bool intersect(const BoundingCircle &circle, const Vector2 &point)
      {
         return intersect(point, circle);
      }

      bool intersect(const BoundingCircle &circle, const LineSegment &segment)
      {
          return intersect(segment, circle);
      }

      bool intersect(const BoundingCircle &circle_a, const BoundingCircle &circle_b)
      {
          float Collision_distance = circle_a.radius_ + circle_b.radius_;
          Vector2 Distance = circle_a.center_ - circle_b.center_;
          if (Distance.length() <= Collision_distance)
          {
              return true;
          }
           else return false;
      }

      bool intersect(const BoundingCircle &circle, const AxisAlignedBoundingBox &aligned_box)
      {
          Vector2 distance_;

          float radius_ = circle.radius_;

          float circle_center_x_ = circle.center_.x_;
          float circle_center_y_ = circle.center_.y_;

          float box_center_x_ = aligned_box.center_.x_;
          float box_center_y_ = aligned_box.center_.y_;

          float left = aligned_box.center_.x_ - aligned_box.half_.x_;
          float right = aligned_box.center_.x_ + aligned_box.half_.x_;
          float top = aligned_box.center_.y_ + aligned_box.half_.y_;
          float bottom = aligned_box.center_.y_ - aligned_box.half_.y_;

          float a_x_ = clamp(circle_center_x_, left, right);
          float a_y_ = clamp(circle_center_y_, bottom, top);

          distance_.x_ = a_x_ - circle_center_x_;
          

          distance_.y_ = a_y_ - circle_center_y_;

          if (distance_.length() <= radius_)
              return true;
              
         return false;
      }

      bool intersect(const AxisAlignedBoundingBox &aligned_box, const Vector2 &point)
      {
         return intersect(point, aligned_box);
      }

      bool intersect(const AxisAlignedBoundingBox &aligned_box, const BoundingCircle &circle)
      {
          return intersect(circle, aligned_box);
      }

      bool intersect(const AxisAlignedBoundingBox &aligned_box_a, const AxisAlignedBoundingBox &aligned_box_b)
      {
		 float a_center_x_ = aligned_box_a.center_.x_;
		 float a_center_y_ = aligned_box_a.center_.y_;

		 float b_center_x_ = aligned_box_b.center_.x_;
		 float b_center_y_ = aligned_box_b.center_.y_;

		 float distance_x = b_center_x_ - a_center_x_;
		 float distance_y = b_center_y_ - a_center_y_;

		 if (distance_x < 0)
		 {
			 distance_x = -distance_x;
		 }

		 if (distance_y < 0)
		 {
			 distance_y = -distance_y;
		 }

		 const float a_half_length_ = aligned_box_a.half_.x_;
		 const float a_half_height_ = aligned_box_a.half_.y_;

		 const float b_half_length_ = aligned_box_b.half_.x_;
		 const float b_half_height_ = aligned_box_b.half_.y_;

		 const float sum_lenght_ = a_half_length_ + b_half_length_;
		 const float sum_height_ = a_half_height_ + b_half_height_;

		 if (distance_x > sum_lenght_)
		 {
			 return false;
		 }
		 if (distance_y > sum_height_)
		 {
			 return false;
		 }
		 else 
			return true;
      }

      // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      // !! TODO: PASS WITH DISTINCTION !!
      // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      bool intersect(const LineSegment &segment_a, const LineSegment &segment_b)
      {
         return false;
      }

      bool intersect(const AxisAlignedBoundingBox &aligned_box, const LineSegment &segment)
      {
         return false;
      }

      bool intersect(const LineSegment &segment, const AxisAlignedBoundingBox &aligned_box)
      {
         return false;
      }

      bool intersect(const ObjectOrientedBoundingBox &oriented_box, const Vector2 &point)
      {
         return false;
      }

      bool intersect(const ObjectOrientedBoundingBox &oriented_box, const LineSegment &segment)
      {
         return false;
      }

      bool intersect(const ObjectOrientedBoundingBox &oriented_box, const BoundingCircle &circle)
      {
         return false;
      }

      bool intersect(const ObjectOrientedBoundingBox &oriented_box, const AxisAlignedBoundingBox &aligned_box)
      {
         return false;
      }

      bool intersect(const ObjectOrientedBoundingBox &oriented_box_a, const ObjectOrientedBoundingBox &oriented_box_b)
      {
         return false;
      }
   } // Collision
} // Helium

