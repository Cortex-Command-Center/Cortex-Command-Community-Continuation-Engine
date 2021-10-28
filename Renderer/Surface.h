#ifndef _RTESURFACE_
#define _RTESURFACE_
extern "C" {
struct SDL_Surface;
}

namespace RTE {
	enum class BitDepth {
		Indexed8,

		BPP32,
	};

	struct sdl_surface_deleter {
		void operator()(SDL_Surface *p);
	};

	class Palette;

	class Surface {
		friend class ContentFile;

	public:
		Surface();
		virtual ~Surface();

		/// <summary>
		/// Create an empty surface with a defined pixelformat of size Width x Height.
		/// </summary>
		/// <param name="width">
		/// The width to set.
		/// </param>
		/// <param name="height">
		/// The height to set.
		/// </param>
		/// <param name="format">
		/// The format this surface will be created with.
		/// </param>
		/// <returns>
		/// True if successful.
		/// </returns>
		virtual bool Create(int width, int height, BitDepth format, std::optional<std::shared_ptr<Palette>> palette = std::nullopt);

		/// <summary>
		/// Returns the stored SDL_Surface. Ownership is not transferred.
		/// </summary>
		/// <returns>
		/// Non owning pointer to the pixels of this surface.
		/// </returns>
		SDL_Surface *GetPixels() { return m_Pixels.get(); }

		/// <summary>
		/// Get the width in pixels of this surface.
		/// </summary>
		/// <returns>
		/// Returnss the width of the surface.
		/// </returns>
		int GetW() const { return m_Width; }

		/// <summary>
		/// Get the height in pixels of this surface.
		/// </summary>
		/// <returns>
		/// Returns the height of this surface.
		/// </returns>
		int GetH() const { return m_Height; }

		glm::vec2 GetSize() { return glm::vec2(m_Width, m_Height); }

		/// <summary>
		/// Get the color value at (x,y) with bounds checking. Return value depends on bitdepth.
		/// </summary>
		/// <param name="x">
		/// The x coordinate to sample.
		/// </param>
		/// <param name="y">
		/// The y coordinate to sample.
		/// </param>
		/// <returns>
		/// The color value of the pixel at (x,y), the format is according to the bitdepth.
		/// </returns>
		uint32_t GetPixel(int x, int y);

		/// <summary>
		/// Get the color index at (x,y) without bounds checking. Behaviour is undefined if called on a 32bpp surface.
		/// </summary>
		/// <param name="x">
		/// The x coordinate to sample.
		/// </param>
		/// <param name="y">
		/// The y coordinate to sample.
		/// </param>
		/// <returns>
		/// The color index of the pixel at (x,y).
		/// </returns>
		unsigned char GetPixel8(int x, int y);

		/// <summary>
		/// Get the color at (x,y) without bounds checking. Behaviour is undefined if called on a 8bpp surface.
		/// </summary>
		/// <param name="x">
		/// The x coordinate to sample.
		/// </param>
		/// <param name="y">
		/// The y coordinate to sample.
		/// </param>
		/// <returns>
		/// The color of the pixel at (x,y).
		/// </returns>
		uint32_t GetPixel32(int x, int y);

		/// <summary>
		/// Set a pixel at (x,y) to the value given by color.
		/// </summary>
		/// <param name="x">
		/// The x position in pixels.
		/// </param>
		/// <param name="y">
		/// The y position in pixels
		/// </param>
		/// <param name="color">
		/// The color to set.
		/// </param>
		void SetPixel(int x, int y, glm::u8vec4 color);

		/// <summary>
		/// Set a pixel at (x,y) to the value given by color.
		/// </summary>
		/// <param name="x">
		/// The x position in pixels.
		/// </param>
		/// <param name="y">
		/// The y position in pixels
		/// </param>
		/// <param name="color">
		/// The color to set in the format of the surface (RGBA32 or I8).
		/// </param>
		void SetPixel(int x, int y, uint32_t color);

		/// <summary>
		/// Set a pixel at (x,y) to the value given by color. No bounds checking is performed.
		/// </summary>
		/// <param name="x">
		/// The x position in pixels.
		/// </param>
		/// <param name="y">
		/// The y position in pixels
		/// </param>
		/// <param name="color">
		/// The index to set.
		/// </param>
		void SetPixel8(int x, int y, unsigned char color);

		/// <summary>
		/// Set a pixel at (x,y) to the value given by color. No bounds checking is performed.
		/// </summary>
		/// <param name="x">
		/// The x position in pixels.
		/// </param>
		/// <param name="y">
		/// The y position in pixels
		/// </param>
		/// <param name="color">
		/// The color to set in ARGB32.
		/// </param>
		void SetPixel32(int x, int y, uint32_t color);

		void blit(Surface &target, int x, int y, double angle = 0, float scaleX = 1.0f, float scaleY = 1.0f) const;

		void blitColor(Surface &target, uint32_t color, int x, int y, double angle = 0, float scaleX = 1.0f, float scaleY = 1.0f) const;

	protected:
		int m_Width;
		int m_Height;
		int m_BPP;

		void SetPalette(std::shared_ptr<Palette> palette) { m_Palette = palette; }

	private:
		std::unique_ptr<SDL_Surface, sdl_surface_deleter> m_Pixels;
		std::shared_ptr<Palette> m_Palette;
	};

} // namespace RTE
#endif
