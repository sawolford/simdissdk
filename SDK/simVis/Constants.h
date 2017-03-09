/* -*- mode: c++ -*- */
/****************************************************************************
 *****                                                                  *****
 *****                   Classification: UNCLASSIFIED                   *****
 *****                    Classified By:                                *****
 *****                    Declassify On:                                *****
 *****                                                                  *****
 ****************************************************************************
 *
 *
 * Developed by: Naval Research Laboratory, Tactical Electronic Warfare Div.
 *               EW Modeling & Simulation, Code 5773
 *               4555 Overlook Ave.
 *               Washington, D.C. 20375-5339
 *
 * License for source code at https://simdis.nrl.navy.mil/License.aspx
 *
 * The U.S. Government retains all rights to use, duplicate, distribute,
 * disclose, or release this software.
 *
 */
#ifndef SIMVIS_CONSTANTS_H
#define SIMVIS_CONSTANTS_H 1

#include <string>
#include "osgDB/Callbacks"
#include "simCore/Common/Common.h"
#include <GL/gl.h>

namespace simVis
{
  // Laser and AnimatedLine line constants:

  /** Maximum length for most Laser and AnimatedLine line segments, in meters */
  static const double MAX_SEGMENT_LENGTH = 5000.0; // meters

  /**
   * Maximum number of segments to subdivide the length of a Laser or AnimatedLine.
   * Will never have more than MAX_NUM_SEGMENTS segments.
   * Prevents excessive subdivision of extremely long lines, choking CPU.
   * Overrides MAX_SEGMENT_LENGTH, so that segments may be longer than MAX_SEGMENT_LENGTH.
   */
  static const unsigned int MAX_NUM_SEGMENTS = 50;

  /**
   * Minimum number of segments to divide the length of a Laser or AnimatedLine.
   * Will never have fewer than MIN_NUM_SEGMENTS segments.
   * Increase this value to reduce the impact of Logarithmic Depth Buffer on long lines that
   * cross through the near plane.  LDB will clip segments too early in some cases, so
   * larger values reduce the impact of the problem at the cost of CPU.
   */
  static const unsigned int MIN_NUM_SEGMENTS = 4;

  /** Minimum length for line segments that are entirely within a threshold value from surface (meters) */
  static const double MAX_SEGMENT_LENGTH_GROUNDED = 100.f;

  /**
  * Threshold value to swap between segment lengths, in meters.  If both ends have altitudes
  * within the threshold value from surface, then the line is subdivided more tightly to
  * reduce collision with surface.
  */
  static const float SUBDIVIDE_BY_GROUND_THRESHOLD = 10.f; // meters altitude

  /** When doing file searches with osgDB, differentiate the search for Windows vs Linux */
#ifdef WIN32
  static const osgDB::CaseSensitivity DEFAULT_CASE_SENSITIVITY = osgDB::CASE_INSENSITIVE;
#else
  static const osgDB::CaseSensitivity DEFAULT_CASE_SENSITIVITY = osgDB::CASE_SENSITIVE;
#endif

  /**
   * Traversal masks for various first-class data model elements
   */
  enum DisplayMask
  {
    DISPLAY_MASK_NONE               = 0,
    DISPLAY_MASK_PLATFORM           = 1 << 0,
    DISPLAY_MASK_BEAM               = 1 << 1,
    DISPLAY_MASK_GATE               = 1 << 2,
    DISPLAY_MASK_PROJECTOR          = 1 << 3,
    DISPLAY_MASK_LASER              = 1 << 4,
    DISPLAY_MASK_LOB_GROUP          = 1 << 5,
    DISPLAY_MASK_LOCAL_GRID         = 1 << 6,
    DISPLAY_MASK_TRACK_HISTORY      = 1 << 7,
    DISPLAY_MASK_LABEL              = 1 << 8,
    DISPLAY_MASK_PLATFORM_MODEL     = 1 << 9,
    DISPLAY_MASK_GOG                = 1 << 10,
    DISPLAY_MASK_ALL                = ~0
  };

  /**
   * Clip planes
   */
  enum ClipPlane
  {
    CLIPPLANE_VISIBLE_HORIZON = 0
  };

  /**
   * Render bin assignments for data model elements
   */
  enum RenderBinNumber
  {
    BIN_TERRAIN             = 0,  // terrain renders in bin 0.
    BIN_GOG_FLAT            = 1,  // terrain-clamped GOG
    BIN_ANIMATEDLINE_FLAT   = 1,  // animated lines clamped to terrain
    BIN_POST_TERRAIN        = 10, // marker ending terrain-clamped items
    BIN_RFPROPAGATION       = 10, // rfprop objects need to be up high since depth buffer is turned off
    BIN_AZIM_ELEV_TOOL      = 11, // Platform Azim/Elev tool rings and text drawn under entities
    BIN_RANGE_TOOL          = 11,
    BIN_ANIMATEDLINE        = 11,
    BIN_AREA_HIGHLIGHT      = 11, // drawn before platforms to avoid platform alpha blend artifacts

    BIN_PLATFORM_MODEL      = 13,
    BIN_LOCAL_GRID          = 13,
    BIN_TRACK_HISTORY       = 13,
    BIN_LASER               = 13,
    BIN_OPAQUE_BEAM         = 13,
    BIN_OPAQUE_GATE         = 13,

    // Transparent items are drawn after opaque items to maximize likelihood of
    // correct colorization.  OSG will sort from back to front in the same render
    // bin, so generally anything with equal graphical priority should share the
    // same render bin ID.
    BIN_PLATFORM_IMAGE      = 15,
    BIN_BEAM                = 15,
    BIN_GATE                = 15,
    BIN_PROJECTOR           = 15,
    BIN_ROCKETBURN          = 15,
    BIN_CYLINDER            = 15,
    BIN_RCS                 = 20, // If shown, RCS will draw on other transparent items
    BIN_LABEL               = 35, // Labels must be drawn after other items to avoid blending artifacts

    BIN_DEPTH_WRITER        = 98, // Locks in depth values prior to SilverLining / Triton, to prevent stacking problems with transparency
    BIN_SILVERLINING        = 99, // SilverLining is automatically drawn at RenderBin 99
    BIN_OCEAN               = 99, // Recommended render bin for Triton and Simple Ocean

    BIN_TOP_1               = 110, // use these values for visuals that should be displayed above anything else in the scene
    BIN_TOP_2               = 115,
    BIN_TOP_3               = 120
  };

  /** Almost all SDK items are depth-sorted */
  static const std::string BIN_GLOBAL_SIMSDK = "DepthSortedBin";
  /** Platforms and some HUD elements are placed into a traversal order bin */
  static const std::string BIN_TRAVERSAL_ORDER_SIMSDK = "TraversalOrderBin";

  /// Stippling mask for gates/beams
  static GLubyte gPatternMask1[] =
  {
    0x44, 0x44, 0x44, 0x44, 0x99, 0x99, 0x99, 0x99,
    0x44, 0x44, 0x44, 0x44, 0x99, 0x99, 0x99, 0x99,
    0x44, 0x44, 0x44, 0x44, 0x99, 0x99, 0x99, 0x99,
    0x44, 0x44, 0x44, 0x44, 0x99, 0x99, 0x99, 0x99,
    0x44, 0x44, 0x44, 0x44, 0x99, 0x99, 0x99, 0x99,
    0x44, 0x44, 0x44, 0x44, 0x99, 0x99, 0x99, 0x99,
    0x44, 0x44, 0x44, 0x44, 0x99, 0x99, 0x99, 0x99,
    0x44, 0x44, 0x44, 0x44, 0x99, 0x99, 0x99, 0x99,
    0x44, 0x44, 0x44, 0x44, 0x99, 0x99, 0x99, 0x99,
    0x44, 0x44, 0x44, 0x44, 0x99, 0x99, 0x99, 0x99,
    0x44, 0x44, 0x44, 0x44, 0x99, 0x99, 0x99, 0x99,
    0x44, 0x44, 0x44, 0x44, 0x99, 0x99, 0x99, 0x99,
    0x44, 0x44, 0x44, 0x44, 0x99, 0x99, 0x99, 0x99,
    0x44, 0x44, 0x44, 0x44, 0x99, 0x99, 0x99, 0x99,
    0x44, 0x44, 0x44, 0x44, 0x99, 0x99, 0x99, 0x99,
    0x44, 0x44, 0x44, 0x44, 0x99, 0x99, 0x99, 0x99
  };

  /// A stippling mask for gates/beams
  static GLubyte gPatternMask2[] =
  {
    0x44, 0x44, 0x44, 0x44, 0x66, 0x66, 0x66, 0x66,
    0x44, 0x44, 0x44, 0x44, 0x66, 0x66, 0x66, 0x66,
    0x44, 0x44, 0x44, 0x44, 0x66, 0x66, 0x66, 0x66,
    0x44, 0x44, 0x44, 0x44, 0x66, 0x66, 0x66, 0x66,
    0x44, 0x44, 0x44, 0x44, 0x66, 0x66, 0x66, 0x66,
    0x44, 0x44, 0x44, 0x44, 0x66, 0x66, 0x66, 0x66,
    0x44, 0x44, 0x44, 0x44, 0x66, 0x66, 0x66, 0x66,
    0x44, 0x44, 0x44, 0x44, 0x66, 0x66, 0x66, 0x66,
    0x44, 0x44, 0x44, 0x44, 0x66, 0x66, 0x66, 0x66,
    0x44, 0x44, 0x44, 0x44, 0x66, 0x66, 0x66, 0x66,
    0x44, 0x44, 0x44, 0x44, 0x66, 0x66, 0x66, 0x66,
    0x44, 0x44, 0x44, 0x44, 0x66, 0x66, 0x66, 0x66,
    0x44, 0x44, 0x44, 0x44, 0x66, 0x66, 0x66, 0x66,
    0x44, 0x44, 0x44, 0x44, 0x66, 0x66, 0x66, 0x66,
    0x44, 0x44, 0x44, 0x44, 0x66, 0x66, 0x66, 0x66,
    0x44, 0x44, 0x44, 0x44, 0x66, 0x66, 0x66, 0x66
  };

  /// A stippling mask for gates/beams
  static GLubyte gPatternMask3[] =
  {
    0x44, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33,
    0x44, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33,
    0x44, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33,
    0x44, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33,
    0x44, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33,
    0x44, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33,
    0x44, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33,
    0x44, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33,
    0x44, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33,
    0x44, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33,
    0x44, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33,
    0x44, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33,
    0x44, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33,
    0x44, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33,
    0x44, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33,
    0x44, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33
  };

  /// A stippling mask for gates/beams
  static GLubyte gPatternMask4[] =
  {
    0xAA, 0xAA, 0xAA, 0xAA, 0x99, 0x99, 0x99, 0x99,
    0xAA, 0xAA, 0xAA, 0xAA, 0x99, 0x99, 0x99, 0x99,
    0xAA, 0xAA, 0xAA, 0xAA, 0x99, 0x99, 0x99, 0x99,
    0xAA, 0xAA, 0xAA, 0xAA, 0x99, 0x99, 0x99, 0x99,
    0xAA, 0xAA, 0xAA, 0xAA, 0x99, 0x99, 0x99, 0x99,
    0xAA, 0xAA, 0xAA, 0xAA, 0x99, 0x99, 0x99, 0x99,
    0xAA, 0xAA, 0xAA, 0xAA, 0x99, 0x99, 0x99, 0x99,
    0xAA, 0xAA, 0xAA, 0xAA, 0x99, 0x99, 0x99, 0x99,
    0xAA, 0xAA, 0xAA, 0xAA, 0x99, 0x99, 0x99, 0x99,
    0xAA, 0xAA, 0xAA, 0xAA, 0x99, 0x99, 0x99, 0x99,
    0xAA, 0xAA, 0xAA, 0xAA, 0x99, 0x99, 0x99, 0x99,
    0xAA, 0xAA, 0xAA, 0xAA, 0x99, 0x99, 0x99, 0x99,
    0xAA, 0xAA, 0xAA, 0xAA, 0x99, 0x99, 0x99, 0x99,
    0xAA, 0xAA, 0xAA, 0xAA, 0x99, 0x99, 0x99, 0x99,
    0xAA, 0xAA, 0xAA, 0xAA, 0x99, 0x99, 0x99, 0x99,
    0xAA, 0xAA, 0xAA, 0xAA, 0x99, 0x99, 0x99, 0x99
  };

  /// A stippling mask for gates/beams
  static GLubyte gPatternMask5[] =
  {
    0xAA, 0xAA, 0xAA, 0xAA, 0x66, 0x66, 0x66, 0x66,
    0xAA, 0xAA, 0xAA, 0xAA, 0x66, 0x66, 0x66, 0x66,
    0xAA, 0xAA, 0xAA, 0xAA, 0x66, 0x66, 0x66, 0x66,
    0xAA, 0xAA, 0xAA, 0xAA, 0x66, 0x66, 0x66, 0x66,
    0xAA, 0xAA, 0xAA, 0xAA, 0x66, 0x66, 0x66, 0x66,
    0xAA, 0xAA, 0xAA, 0xAA, 0x66, 0x66, 0x66, 0x66,
    0xAA, 0xAA, 0xAA, 0xAA, 0x66, 0x66, 0x66, 0x66,
    0xAA, 0xAA, 0xAA, 0xAA, 0x66, 0x66, 0x66, 0x66,
    0xAA, 0xAA, 0xAA, 0xAA, 0x66, 0x66, 0x66, 0x66,
    0xAA, 0xAA, 0xAA, 0xAA, 0x66, 0x66, 0x66, 0x66,
    0xAA, 0xAA, 0xAA, 0xAA, 0x66, 0x66, 0x66, 0x66,
    0xAA, 0xAA, 0xAA, 0xAA, 0x66, 0x66, 0x66, 0x66,
    0xAA, 0xAA, 0xAA, 0xAA, 0x66, 0x66, 0x66, 0x66,
    0xAA, 0xAA, 0xAA, 0xAA, 0x66, 0x66, 0x66, 0x66,
    0xAA, 0xAA, 0xAA, 0xAA, 0x66, 0x66, 0x66, 0x66,
    0xAA, 0xAA, 0xAA, 0xAA, 0x66, 0x66, 0x66, 0x66
  };

  /// A stippling mask for gates/beams
  static GLubyte gPatternMask6[] =
  {
    0xAA, 0xAA, 0xAA, 0xAA, 0x33, 0x33, 0x33, 0x33,
    0xAA, 0xAA, 0xAA, 0xAA, 0x33, 0x33, 0x33, 0x33,
    0xAA, 0xAA, 0xAA, 0xAA, 0x33, 0x33, 0x33, 0x33,
    0xAA, 0xAA, 0xAA, 0xAA, 0x33, 0x33, 0x33, 0x33,
    0xAA, 0xAA, 0xAA, 0xAA, 0x33, 0x33, 0x33, 0x33,
    0xAA, 0xAA, 0xAA, 0xAA, 0x33, 0x33, 0x33, 0x33,
    0xAA, 0xAA, 0xAA, 0xAA, 0x33, 0x33, 0x33, 0x33,
    0xAA, 0xAA, 0xAA, 0xAA, 0x33, 0x33, 0x33, 0x33,
    0xAA, 0xAA, 0xAA, 0xAA, 0x33, 0x33, 0x33, 0x33,
    0xAA, 0xAA, 0xAA, 0xAA, 0x33, 0x33, 0x33, 0x33,
    0xAA, 0xAA, 0xAA, 0xAA, 0x33, 0x33, 0x33, 0x33,
    0xAA, 0xAA, 0xAA, 0xAA, 0x33, 0x33, 0x33, 0x33,
    0xAA, 0xAA, 0xAA, 0xAA, 0x33, 0x33, 0x33, 0x33,
    0xAA, 0xAA, 0xAA, 0xAA, 0x33, 0x33, 0x33, 0x33,
    0xAA, 0xAA, 0xAA, 0xAA, 0x33, 0x33, 0x33, 0x33,
    0xAA, 0xAA, 0xAA, 0xAA, 0x33, 0x33, 0x33, 0x33
  };

  /// A stippling mask for gates/beams
  static GLubyte gPatternMask7[] =
  {
    0xDD, 0xDD, 0xDD, 0xDD, 0x99, 0x99, 0x99, 0x99,
    0xDD, 0xDD, 0xDD, 0xDD, 0x99, 0x99, 0x99, 0x99,
    0xDD, 0xDD, 0xDD, 0xDD, 0x99, 0x99, 0x99, 0x99,
    0xDD, 0xDD, 0xDD, 0xDD, 0x99, 0x99, 0x99, 0x99,
    0xDD, 0xDD, 0xDD, 0xDD, 0x99, 0x99, 0x99, 0x99,
    0xDD, 0xDD, 0xDD, 0xDD, 0x99, 0x99, 0x99, 0x99,
    0xDD, 0xDD, 0xDD, 0xDD, 0x99, 0x99, 0x99, 0x99,
    0xDD, 0xDD, 0xDD, 0xDD, 0x99, 0x99, 0x99, 0x99,
    0xDD, 0xDD, 0xDD, 0xDD, 0x99, 0x99, 0x99, 0x99,
    0xDD, 0xDD, 0xDD, 0xDD, 0x99, 0x99, 0x99, 0x99,
    0xDD, 0xDD, 0xDD, 0xDD, 0x99, 0x99, 0x99, 0x99,
    0xDD, 0xDD, 0xDD, 0xDD, 0x99, 0x99, 0x99, 0x99,
    0xDD, 0xDD, 0xDD, 0xDD, 0x99, 0x99, 0x99, 0x99,
    0xDD, 0xDD, 0xDD, 0xDD, 0x99, 0x99, 0x99, 0x99,
    0xDD, 0xDD, 0xDD, 0xDD, 0x99, 0x99, 0x99, 0x99,
    0xDD, 0xDD, 0xDD, 0xDD, 0x99, 0x99, 0x99, 0x99
  };

  /// A stippling mask for gates/beams
  static GLubyte gPatternMask8[] =
  {
    0xDD, 0xDD, 0xDD, 0xDD, 0x66, 0x66, 0x66, 0x66,
    0xDD, 0xDD, 0xDD, 0xDD, 0x66, 0x66, 0x66, 0x66,
    0xDD, 0xDD, 0xDD, 0xDD, 0x66, 0x66, 0x66, 0x66,
    0xDD, 0xDD, 0xDD, 0xDD, 0x66, 0x66, 0x66, 0x66,
    0xDD, 0xDD, 0xDD, 0xDD, 0x66, 0x66, 0x66, 0x66,
    0xDD, 0xDD, 0xDD, 0xDD, 0x66, 0x66, 0x66, 0x66,
    0xDD, 0xDD, 0xDD, 0xDD, 0x66, 0x66, 0x66, 0x66,
    0xDD, 0xDD, 0xDD, 0xDD, 0x66, 0x66, 0x66, 0x66,
    0xDD, 0xDD, 0xDD, 0xDD, 0x66, 0x66, 0x66, 0x66,
    0xDD, 0xDD, 0xDD, 0xDD, 0x66, 0x66, 0x66, 0x66,
    0xDD, 0xDD, 0xDD, 0xDD, 0x66, 0x66, 0x66, 0x66,
    0xDD, 0xDD, 0xDD, 0xDD, 0x66, 0x66, 0x66, 0x66,
    0xDD, 0xDD, 0xDD, 0xDD, 0x66, 0x66, 0x66, 0x66,
    0xDD, 0xDD, 0xDD, 0xDD, 0x66, 0x66, 0x66, 0x66,
    0xDD, 0xDD, 0xDD, 0xDD, 0x66, 0x66, 0x66, 0x66,
    0xDD, 0xDD, 0xDD, 0xDD, 0x66, 0x66, 0x66, 0x66
  };

  /// A stippling mask for gates/beams
  static GLubyte gPatternMask9[] =
  {
    0xDD, 0xDD, 0xDD, 0xDD, 0x33, 0x33, 0x33, 0x33,
    0xDD, 0xDD, 0xDD, 0xDD, 0x33, 0x33, 0x33, 0x33,
    0xDD, 0xDD, 0xDD, 0xDD, 0x33, 0x33, 0x33, 0x33,
    0xDD, 0xDD, 0xDD, 0xDD, 0x33, 0x33, 0x33, 0x33,
    0xDD, 0xDD, 0xDD, 0xDD, 0x33, 0x33, 0x33, 0x33,
    0xDD, 0xDD, 0xDD, 0xDD, 0x33, 0x33, 0x33, 0x33,
    0xDD, 0xDD, 0xDD, 0xDD, 0x33, 0x33, 0x33, 0x33,
    0xDD, 0xDD, 0xDD, 0xDD, 0x33, 0x33, 0x33, 0x33,
    0xDD, 0xDD, 0xDD, 0xDD, 0x33, 0x33, 0x33, 0x33,
    0xDD, 0xDD, 0xDD, 0xDD, 0x33, 0x33, 0x33, 0x33,
    0xDD, 0xDD, 0xDD, 0xDD, 0x33, 0x33, 0x33, 0x33,
    0xDD, 0xDD, 0xDD, 0xDD, 0x33, 0x33, 0x33, 0x33,
    0xDD, 0xDD, 0xDD, 0xDD, 0x33, 0x33, 0x33, 0x33,
    0xDD, 0xDD, 0xDD, 0xDD, 0x33, 0x33, 0x33, 0x33,
    0xDD, 0xDD, 0xDD, 0xDD, 0x33, 0x33, 0x33, 0x33,
    0xDD, 0xDD, 0xDD, 0xDD, 0x33, 0x33, 0x33, 0x33
  };

} // namespace simVis

#endif // SIMVIS_CONSTANTS_H

