/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-23 16:21:01
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-23 16:21:22
 * @FilePath: /OpenGL_Tutorials/april/renderer/backend/opengl/DeviceInfoGL.h
 */

#pragma once

#include "../DeviceInfo.h"

namespace april {
namespace backend {

/**
 * Used to query features and implementation limits
 */
class DeviceInfoGL : public DeviceInfo {
 public:
  DeviceInfoGL() = default;
  virtual ~DeviceInfoGL() = default;

  /**
   * Gather features and implementation limits
   */
  virtual bool init() override;

  /**
   * Get vendor device name.
   * @return Vendor device name.
   */
  virtual const char* getVendor() const override;

  /**
   * Get the full name of the vendor device.
   * @return The full name of the vendor device.
   */
  virtual const char* getRenderer() const override;

  /**
   * Get version name.
   * @return Version name.
   */
  virtual const char* getVersion() const override;

  /**
   * get OpenGL ES extensions.
   * @return Extension supported by OpenGL ES.
   */
  virtual const char* getExtension() const override;

  /**
   * Check if feature supported by OpenGL ES.
   * @param feature Specify feature to be query.
   * @return true if the feature is supported, false otherwise.
   */
  virtual bool checkForFeatureSupported(FeatureType feature) override;

 private:
  bool checkForGLExtension(const std::string& searchName) const;

  std::string _glExtensions;
};

}  // namespace backend
}  // namespace april