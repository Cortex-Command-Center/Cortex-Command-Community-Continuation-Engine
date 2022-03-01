#ifndef _RTESETTINGSMAN_
#define _RTESETTINGSMAN_

#include "Serializable.h"
#include "Singleton.h"

#define g_SettingsMan SettingsMan::Instance()

namespace RTE {

	/// <summary>
	/// The singleton manager over the application and misc settings.
	/// </summary>
	class SettingsMan : public Singleton<SettingsMan>, public Serializable {

	public:

		SerializableClassNameGetter;
		SerializableOverrideMethods;

#pragma region Creation
		/// <summary>
		/// Constructor method used to instantiate a SettingsMan object in system memory. Initialize() should be called before using the object.
		/// </summary>
		SettingsMan() { Clear(); }

		/// <summary>
		/// Makes the SettingsMan object ready for use.
		/// </summary>
		/// <returns>An error return value signaling success or any particular failure. Anything below 0 is an error signal.</returns>
		int Initialize();
#pragma endregion

#pragma region Destruction
		/// <summary>
		/// Resets the entire SettingsMan, including its inherited members, to their default settings or values.
		/// </summary>
		void Reset() override { Clear(); }
#pragma endregion

#pragma region Settings Manager Operations
		/// <summary>
		/// Gets whether Settings.ini needs to be overwritten with the complete list of settings or not. Will be true only if Settings.ini was created with default values on first load or after settings delete.
		/// </summary>
		/// <returns>Whether Settings.ini needs to be overwritten with the complete list of settings or not.</returns>
		bool SettingsNeedOverwrite() const { return m_SettingsNeedOverwrite; }

		/// <summary>
		/// Sets Settings.ini to be overwritten during the boot sequence for overrides to be applied (e.g. resolution validation).
		/// </summary>
		void SetSettingsNeedOverwrite() { m_SettingsNeedOverwrite = true; }

		/// <summary>
		/// Overwrites the settings file to save changes made from within the game.
		/// </summary>
		void UpdateSettingsFile() const;
#pragma endregion

#pragma region Engine Settings
		/// <summary>
		/// Returns the recommended MOID count. If this amount is exceeded then some units may be removed at the start of the activity.
		/// </summary>
		/// <returns>Recommended MOID count.</returns>
		int RecommendedMOIDCount() const { return m_RecommendedMOIDCount; }

		/// <summary>
		/// Gets whether simplified collision detection (reduced MOID layer sampling) is enabled.
		/// </summary>
		/// <returns>Whether simplified collision detection is enabled or not.</returns>
		bool SimplifiedCollisionDetection() const { return m_SimplifiedCollisionDetection; }
#pragma endregion

#pragma region Gameplay Settings
		/// <summary>
		/// Returns true if endless MetaGame mode is enabled.
		/// </summary>
		/// <returns>Whether endless mode is enabled via settings.</returns>
		bool EndlessMetaGameMode() const { return m_EndlessMetaGameMode; }

		/// <summary>
		/// Sets whether endless MetaGame mode is enabled or not.
		/// </summary>
		/// <param name="enable">Whether endless MetaGame mode is enabled or not.</param>
		void SetEndlessMetaGameMode(bool enable) { m_EndlessMetaGameMode = enable; }

		/// <summary>
		/// Whether we need to play blips when unseen layer is revealed.
		/// </summary>
		/// <returns>Whether we need to play blips when unseen layer is revealed.</returns>
		bool BlipOnRevealUnseen() const { return m_BlipOnRevealUnseen; }

		/// <summary>
		/// Sets whether we need to play blips when unseen layer is revealed.
		/// </summary>
		/// <param name="newValue">New value for Blip on reveal unseen option.</param>
		void SetBlipOnRevealUnseen(bool newValue) { m_BlipOnRevealUnseen = newValue; }

		/// <summary>
		/// Gets the range in which devices on Scene will show the pick-up HUD.
		/// </summary>
		/// <returns>The range in which devices on Scene will show the pick-up HUD, in pixels. 0 means HUDs are hidden, -1 means unlimited range.</returns>
		float GetUnheldItemsHUDDisplayRange() const { return m_UnheldItemsHUDDisplayRange; }

		/// <summary>
		/// Sets the range in which devices on Scene will show the pick-up HUD.
		/// </summary>
		/// <param name="newRadius">The new range in which devices on Scene will show the pick-up HUD, in pixels. 0 means HUDs are hidden, -1 means unlimited range.</param>
		void SetUnheldItemsHUDDisplayRange(float newRadius) { m_UnheldItemsHUDDisplayRange = std::floor(newRadius); }

		/// <summary>
		/// Gets whether or not devices on Scene should always show their pick-up HUD when the player is in strategic mode.
		/// </summary>
		/// <returns>Whether or not devices on Scene should always show their pick-up HUD when the player is in strategic mode.</returns>
		bool AlwaysDisplayUnheldItemsInStrategicMode() const { return m_AlwaysDisplayUnheldItemsInStrategicMode; }

		/// <summary>
		/// Sets whether or not devices on Scene should always show their pick-up HUD when the player is in strategic mode.
		/// </summary>
		/// <param name="shouldShowUnheldItemsInStrategicMode">Whether or not devices on Scene should always show their pick-up HUD when the player is in strategic mode.</param>
		void SetAlwaysDisplayUnheldItemsInStrategicMode(bool shouldShowUnheldItemsInStrategicMode) { m_AlwaysDisplayUnheldItemsInStrategicMode = shouldShowUnheldItemsInStrategicMode; }

		/// <summary>
		/// Whether red and white flashes appear when brain is damaged.
		/// </summary>
		/// <returns>Whether red and white flashes appear when brain is damaged.</returns>
		bool FlashOnBrainDamage() const { return m_FlashOnBrainDamage; }

		/// <summary>
		/// Sets whether red and white flashes appear when brain is damaged.
		/// </summary>
		/// <param name="newValue">New value for Flash on brain damage setting.</param>
		void SetFlashOnBrainDamage(bool newValue) { m_FlashOnBrainDamage = newValue; }

		/// <summary>
		/// Whether we need to show items from other factions in buy menu GUI.
		/// </summary>
		/// <returns>True if we need to show foreign items.</returns>
		bool ShowForeignItems() const { return m_ShowForeignItems; }

		/// <summary>
		/// Set whether we need to show items from other factions in buy menu GUI.
		/// </summary>
		/// <param name="newValue">If we need to show foreign items.</param>
		void SetShowForeignItems(bool newValue) { m_ShowForeignItems = newValue; }

		/// <summary>
		/// Gets whether the crab bomb effect is enabled or not.
		/// </summary>
		/// <returns>Whether the crab bomb effect is enabled or not. False means releasing whatever number of crabs will do nothing except release whatever number of crabs.</returns>
		bool CrabBombsEnabled() const { return m_EnableCrabBombs; }

		/// <summary>
		/// Sets whether the crab bomb effect is enabled or not.
		/// </summary>
		/// <param name="enable">Enable the crab bomb effect or not. False means releasing whatever number of crabs will do nothing except release whatever number of crabs.</param>
		void SetCrabBombsEnabled(bool enable) { m_EnableCrabBombs = enable; }

		/// <summary>
		/// Gets the number of crabs needed to be released at once to trigger the crab bomb effect.
		/// </summary>
		/// <returns>The number of crabs needed to be released at once to trigger the crab bomb effect.</returns>
		int GetCrabBombThreshold() const { return m_CrabBombThreshold; }

		/// <summary>
		/// Sets the number of crabs needed to be released at once to trigger the crab bomb effect.
		/// </summary>
		/// <param name="newThreshold">The new number of crabs needed to be released at once to trigger the crab bomb effect.</param>
		void SetCrabBombThreshold(int newThreshold) { m_CrabBombThreshold = newThreshold; }

		/// <summary>
		/// Gets whether the HUD of enemy Actors is set to be visible to the player or not.
		/// </summary>
		/// <returns>Whether the HUD of enemy Actors is visible to the player.</returns>
		bool ShowEnemyHUD() const { return m_ShowEnemyHUD; }

		/// <summary>
		/// Sets whether the HUD of enemy Actors should to be visible to the player or not.
		/// </summary>
		/// <param name="showHUD">Whether the HUD of enemy Actors should be visible to the player or not.</param>
		void SetShowEnemyHUD(bool showHUD) { m_ShowEnemyHUD = showHUD; }

		/// <summary>
		/// Gets whether smart BuyMenu navigation is enabled, meaning swapping to equipment mode and back will change active tabs in the BuyMenu.
		/// </summary>
		/// <returns>Whether smart BuyMenu navigation is enabled or not.</returns>
		bool SmartBuyMenuNavigationEnabled() const { return m_EnableSmartBuyMenuNavigation; }

		/// <summary>
		/// Sets whether smart BuyMenu navigation is enabled, meaning swapping to equipment mode and back will change active tabs in the BuyMenu.
		/// </summary>
		/// <param name="enable">Whether to enable smart BuyMenu navigation or not.</param>
		void SetSmartBuyMenuNavigation(bool enable) { m_EnableSmartBuyMenuNavigation = enable; }
#pragma endregion

#pragma region Editor Settings
		/// <summary>
		/// Returns the list of visible assembly groups.
		/// </summary>
		/// <returns>List of visible assembly groups.</returns>
		std::list<std::string> GetVisibleAssemblyGroupsList() const { return m_VisibleAssemblyGroupsList; }

		/// <summary>
		/// Whether editors will allow to select Base.rte as a module to save in
		/// </summary>
		/// <returns>True of editors are allowed to select Base.rte as a module to save in.</returns>
		bool AllowSavingToBase() const { return m_AllowSavingToBase; }

		/// <summary>
		/// Whether we need to show MetaScenes in editors and scenario UI.
		/// </summary>
		/// <returns>True if we need to show MetaScenes.</returns>
		bool ShowMetascenes() const { return m_ShowMetaScenes; }
#pragma endregion

#pragma region Mod and Script Management
		/// <summary>
		/// Gets the map of mods which are disabled.
		/// </summary>
		/// <returns>Map of mods which are disabled.</returns>
		std::map<std::string, bool> & GetDisabledModsMap() { return m_DisabledMods; }

		/// <summary>
		/// Gets whether the specified mod is disabled in the settings.
		/// </summary>
		/// <param name="modModule">Mod to check.</param>
		/// <returns>Whether the mod is disabled via settings.</returns>
		bool IsModDisabled(const std::string &modModule) const { return (m_DisabledMods.find(modModule) != m_DisabledMods.end()) ? m_DisabledMods.at(modModule) : false; }

		/// <summary>
		/// Gets the map of global scripts which are enabled.
		/// </summary>
		/// <returns>Map of global scripts which are enabled.</returns>
		std::map<std::string, bool> & GetEnabledGlobalScriptMap() { return m_EnabledGlobalScripts; }

		/// <summary>
		/// Gets whether the specified global script is enabled in the settings.
		/// </summary>
		/// <param name="scriptName">Global script to check.</param>
		/// <returns>Whether the global script is enabled via settings.</returns>
		bool IsGlobalScriptEnabled(const std::string &scriptName) const { return (m_EnabledGlobalScripts.find(scriptName) != m_EnabledGlobalScripts.end()) ? m_EnabledGlobalScripts.at(scriptName) : false; }
#pragma endregion

#pragma region Misc Settings
		/// <summary>
		/// Gets whether the game intro is set to be skipped on game startup or not.
		/// </summary>
		/// <returns>Whether intro is set to be skipped or not.</returns>
		bool SkipIntro() const { return m_SkipIntro; }

		/// <summary>
		/// Sets whether the game intro should be skipped on game startup or not.
		/// </summary>
		/// <param name="play">Whether to skip game intro or not.</param>
		void SetSkipIntro(bool play) { m_SkipIntro = play; }

		/// <summary>
		/// Gets whether tooltip display on certain UI elements is enabled or not.
		/// </summary>
		/// <returns>Whether tooltips are displayed or not.</returns>
		bool ShowToolTips() const { return m_ShowToolTips; }

		/// <summary>
		/// Sets whether to display tooltips on certain UI elements or not.
		/// </summary>
		/// <param name="showToolTips">Whether to display tooltips or not.</param>
		void SetShowToolTips(bool showToolTips) { m_ShowToolTips = showToolTips; }

		/// <summary>
		/// Gets whether to draw AtomGroup visualizations or not.
		/// </summary>
		/// <returns>Whether to draw AtomGroup visualizations or not.</returns>
		bool DrawAtomGroupVisualizations() const { return m_DrawAtomGroupVisualizations; }

		/// <summary>
		/// Sets whether to draw AtomGroup visualizations or not.
		/// </summary>
		/// <param name="drawAtomGroupVisualizations">Whether to draw AtomGroup visualizations or not.</param>
		void SetDrawAtomGroupVisualizations(bool drawAtomGroupVisualizations) { m_DrawAtomGroupVisualizations = drawAtomGroupVisualizations; }

		/// <summary>
		/// Gets whether to draw HandGroup and FootGroup visualizations or not.
		/// </summary>
		/// <returns>Whether to draw HandGroup and FootGroup visualizations or not.</returns>
		bool DrawHandAndFootGroupVisualizations() const { return m_DrawHandAndFootGroupVisualizations; }

		/// <summary>
		/// Sets whether to draw HandGroup and FootGroup visualizations or not.
		/// </summary>
		/// <param name="drawHandAndFootGroupVisualizations">Whether to draw HandGroup and FootGroup visualizations or not.</param>
		void SetDrawHandAndFootGroupVisualizations(bool drawHandAndFootGroupVisualizations) { m_DrawHandAndFootGroupVisualizations = drawHandAndFootGroupVisualizations; }

		/// <summary>
		/// Gets whether to draw LimbPath visualizations or not.
		/// </summary>
		/// <returns>Whether to draw LimbPath visualizations or not.</returns>
		bool DrawLimbPathVisualizations() const { return m_DrawLimbPathVisualizations; }

		/// <summary>
		/// Sets whether to draw LimbPath visualizations or not.
		/// </summary>
		/// <param name="drawAtomGroupVisualizations">Whether to draw AtomGroup visualizations or not.</param>
		void SetDrawLimbPathVisualizations(bool drawLimbPathVisualizations) { m_DrawLimbPathVisualizations = drawLimbPathVisualizations; }

		/// <summary>
		/// Gets whether debug print mode is enabled or not.
		/// </summary>
		/// <returns>Whether debug print mode is enabled or not.</returns>
		bool PrintDebugInfo() const { return m_PrintDebugInfo; }

		/// <summary>
		/// Sets print debug info mode.
		/// </summary>
		/// <param name="printDebugInfo">New debug print mode value.</param>
		void SetPrintDebugInfo(bool printDebugInfo) { m_PrintDebugInfo = printDebugInfo; }

		/// <summary>
		/// Gets whether displaying the reader progress report during module loading is disabled or not.
		/// </summary>
		/// <returns>Whether the reader progress report is being displayed during module loading or not.</returns>
		bool GetLoadingScreenProgressReportDisabled() const { return m_DisableLoadingScreenProgressReport; }

		/// <summary>
		/// Sets whether the reader progress report should be displayed during module loading or not.
		/// </summary>
		/// <param name="disable">Whether to display the reader progress report during module loading or not.</param>
		void SetLoadingScreenProgressReportDisabled(bool disable) { m_DisableLoadingScreenProgressReport = disable; }

		/// <summary>
		/// Gets how accurately the reader progress report tells what line it's reading during module loading.
		/// </summary>
		/// <returns>How accurately the reader progress report tells what line it's reading during module loading.</returns>
		int LoadingScreenProgressReportPrecision() const { return m_LoadingScreenProgressReportPrecision; }

		/// <summary>
		/// Gets the multiplier value for the transition durations between different menus.
		/// </summary>
		/// <returns>The multiplier value for the transition durations between different menus. Lower values equal faster transitions.</returns>
		float GetMenuTransitionDurationMultiplier() const { return m_MenuTransitionDurationMultiplier; }

		/// <summary>
		/// Sets the multiplier value for the transition durations between different menus.
		/// </summary>
		/// <param name="newSpeed">New multiplier value for the transition durations between different menus. Lower values equal faster transitions.</param>
		void SetMenuTransitionDurationMultiplier(float newSpeed) { m_MenuTransitionDurationMultiplier = std::max(0.0F, newSpeed); }

		/// <summary>
		/// Gets whether the duration of module loading (extraction included) is being measured or not. For benchmarking purposes.
		/// </summary>
		/// <returns>Whether duration is being measured or not.</returns>
		bool IsMeasuringModuleLoadTime() const { return m_MeasureModuleLoadTime; }

		/// <summary>
		/// Sets whether the duration of module loading (extraction included) should be measured or not. For benchmarking purposes.
		/// </summary>
		/// <param name="measure">Whether duration should be measured or not.</param>
		void MeasureModuleLoadTime(bool measure) { m_MeasureModuleLoadTime = measure; }
#pragma endregion

	protected:

		bool m_SettingsNeedOverwrite; //!< Whether the settings file was generated with minimal defaults and needs to be overwritten to be fully populated.

		bool m_ShowForeignItems; //!< Do not show foreign items in buy menu.
		bool m_FlashOnBrainDamage; //!< Whether red flashes on brain damage are on or off.
		bool m_BlipOnRevealUnseen; //!< Blip if unseen is revealed.
		float m_UnheldItemsHUDDisplayRange; //!< Range in which devices on Scene will show the pick-up HUD, in pixels. 0 means HUDs are hidden, -1 means unlimited range.
		bool m_AlwaysDisplayUnheldItemsInStrategicMode; //!< Whether or not devices on Scene should always show their pick-up HUD when when the player is in strategic mode.
		bool m_EndlessMetaGameMode; //!< Endless MetaGame mode.
		bool m_EnableCrabBombs; //!< Whether all actors (except Brains and Doors) should be annihilated if a number exceeding the crab bomb threshold is released at once.
		int m_CrabBombThreshold; //!< The number of crabs needed to be released at once to trigger the crab bomb effect.
		bool m_ShowEnemyHUD; //!< Whether the HUD of enemy actors should be visible to the player.
		bool m_EnableSmartBuyMenuNavigation; //!< Whether swapping to equipment mode and back should change active tabs in the BuyMenu.

		bool m_AllowSavingToBase; //!< Whether editors will allow to select Base.rte as a module to save in.
		bool m_ShowMetaScenes; //!< Show MetaScenes in editors and activities.

		int m_RecommendedMOIDCount; //!< Recommended max MOID's before removing actors from scenes.
		bool m_SimplifiedCollisionDetection; //!< Whether simplified collision detection (reduced MOID layer sampling) is enabled.

		bool m_SkipIntro; //!< Whether to play the intro of the game or skip directly to the main menu.
		bool m_ShowToolTips; //!< Whether ToolTips are enabled or not.
		bool m_DisableLoadingScreenProgressReport; //!< Whether to display the reader progress report during module loading or not. Greatly increases loading speeds when disabled.
		int m_LoadingScreenProgressReportPrecision; //!< How accurately the reader progress report tells what line it's reading during module loading. Lower values equal more precision at the cost of loading speed.
		float m_MenuTransitionDurationMultiplier; //!< Multiplier value for the transition durations between different menus. Lower values equal faster transitions.

		bool m_DrawAtomGroupVisualizations; //!< Whether to draw MOSRotating AtomGroups to the Scene MO color Bitmap.
		bool m_DrawHandAndFootGroupVisualizations; //!< Whether to draw Actor HandGroups and FootGroups to the Scene MO color Bitmap.
		bool m_DrawLimbPathVisualizations; //!< Whether to draw Actor LimbPaths to the Scene MO color Bitmap.
		bool m_PrintDebugInfo; //!< Print some debug info in console.
		bool m_MeasureModuleLoadTime; //!< Whether to measure the duration of data module loading (extraction included). For benchmarking purposes.

		std::list<std::string> m_VisibleAssemblyGroupsList; //!< List of assemblies groups always shown in editors.
		std::map<std::string, bool> m_DisabledMods; //!< Map of the module names we disabled.
		std::map<std::string, bool> m_EnabledGlobalScripts; //!< Map of the global script names we enabled.

	private:

		static const std::string c_ClassName; //!< A string with the friendly-formatted type name of this.

		std::string m_SettingsPath; //!< String containing the Path to the Settings.ini file.

		/// <summary>
		/// Clears all the member variables of this SettingsMan, effectively resetting the members of this abstraction level only.
		/// </summary>
		void Clear();

		// Disallow the use of some implicit methods.
		SettingsMan(const SettingsMan &reference) = delete;
		SettingsMan & operator=(const SettingsMan &rhs) = delete;
	};
}
#endif
