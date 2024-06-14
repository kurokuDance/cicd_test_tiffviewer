#pragma once
#include<iostream>
#include<map>
#include<vector>

struct TagValue {
    int numericValue;
    std::string constant;
};

std::map<int, std::vector<TagValue>> Tags = {
    {254,
     {{0, "NewSubfileType"},
      {1, "Main image"},
      {2, "Thumbnail image"},
      {4, "Reduced-resolution image"}}},

    {255,
     {{1, "SubfileType"},
      {2, "Image"},
      {3, "ReducedImage"},
      {4, "Page"}}},

    {259,
     {{1, "COMPRESSION_NONE"},
      {2, "COMPRESSION_CCITTRLE"},
      {3, "COMPRESSION_CCITTFAX3"},
      {4, "COMPRESSION_CCITTFAX4"},
      {5, "COMPRESSION_LZW"},
      {6, "COMPRESSION_OJPEG"},
      {7, "COMPRESSION_JPEG"},
      {32766, "COMPRESSION_NEXT"},
      {32771, "COMPRESSION_CCITTRLEW"},
      {32773, "COMPRESSION_PACKBITS"},
      {32809, "COMPRESSION_THUNDERSCAN"},
      {32895, "COMPRESSION_IT8CTPAD"},
      {32896, "COMPRESSION_IT8LW"},
      {32897, "COMPRESSION_IT8MP"},
      {32898, "COMPRESSION_IT8BL"},
      {32908, "COMPRESSION_PIXARFILM"},
      {32909, "COMPRESSION_PIXARLOG"},
      {32946, "COMPRESSION_DEFLATE"},
      {8, "COMPRESSION_ADOBE_DEFLATE"},
      {32947, "COMPRESSION_DCS"},
      {34661, "COMPRESSION_JBIG"},
      {34676, "COMPRESSION_SGILOG"},
      {34677, "COMPRESSION_SGILOG24"},
      {34712, "COMPRESSION_JP2000"}}},

    {262,
     {{0, "PhotometricInterpretation_WHITE_IS_ZERO"},
      {1, "PhotometricInterpretation_BLACK_IS_ZERO"},
      {2, "PhotometricInterpretation_RGB"},
      {3, "PhotometricInterpretation_Palette color"},
      {4, "PhotometricInterpretation_Transparency mask"},
      {5, "PHOTOMETRIC_SEPARATED "},
      {6, "PHOTOMETRIC_YCBCR "},
      {8, "PHOTOMETRIC_CIELAB "},
      {9, "PHOTOMETRIC_ICCLAB "},
      {10, "PHOTOMETRIC_ITULAB"},
      {32844, "PHOTOMETRIC_LOGL "},
      {32845, "PhotometricInterpretation_LOGLUV"}}},

    {263,
     {{0, "Threshholding_NONE"},
      {1, "Threshholding_DITHERED"}}},


    {266,
        {{1, "FillOrder_HIGHFILL"},
         {2, "FillOrder_LOWFILL"}},},


    {274,
        {{1, "Orientation_TOPLEFT"},
         {2, "Orientation_TOPRIGHT"},
         {3, "Orientation_BOTRIGHT"},
         {4, "Orientation_BOTLEFT"},
         {5, "Orientation_LEFTTOP"},
         {6, "Orientation_RIGHTTOP"},
         {7, "Orientation_RIGHTBOT"},
         {8, "Orientation_LEFTBOT"}},},

    {284,
        {{1, "PLANARCONFIG_CONTIG "},
         {2, "PLANARCONFIG_SEPARATE "}},},

    {296,
        {{1, "ResolutionUnit_NONE"},
         {2, "ResolutionUnit_INCHES"},
         {3, "ResolutionUnit_CENTIMETERS"}},},

    {317,
        {{1, "Predictor_NONE"},
         {2, "Predictor_HORIZONTAL_DIFFERENCING"}},},


    {332,
        {{1, "InkSet_CMYK"},
         {2, "InkSet_MULTICOMPONENT"}},},


    };

