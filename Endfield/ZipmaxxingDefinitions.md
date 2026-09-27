# General

- **Out-Of-Bounds (OOB)**: Outside of valid playable bounds. *(i.e. spots that require unintended parkour or breaking through invisible walls)*

- **Fall Timer / Air Timer**: An internal timer that counts down any time the operators is falling or actively ascending in the air where the operators is force teleported to the last valid position once it runs out. *(30s **before** v1.2, 100s **after**)*

- **Zippable / Not Zippable**: When two areas can/cannot be crossed with a zipline.

- **Zipline**: You know what this is lol.
	* **Anti-Zipline Coating**: A piece of terrain or structure on which there are no valid 3x3 and a nearby 2x2 spots for a zipline + a pylon to be placed. *(Does not include lack of space, mostly used for intentional splatter of red AIC tiles)*
	* **"Angel" Zipline**: A subset of ziplines that are mysteriously shared amongst users without a possible power source. *(i.e., "Wireless Little Angel" spreading around the CN servers)*
	* **Floating Zipline**: A zipline where the terrain underneth was moved during map changes but the AIC tiles were not refreshed, resulting in it floating in the air. *(i.e. West Jingyu Pergola Zipline)*
	* **Bricked Zipline**: [DEPRECIATED: see **Invalid Zip**] A zipline where a piece of terrain or invisible wall was placed over it during map changes, resulting in it being bricked permanently if the player cannot access it. *(Since v1.4, bricked zips are no longer a thing as you can remotely stash facilities)*
	* **Invalid Zip**: When a zipline that was previously placed in a valid position is no longer located in one due to terrain changes with game updates. *(These facilities will appear **red** on the map and will get auto-stashed in 90 days)*
	* **"Blue Zip"**: Alias for ziplines shared to you.

- **Invisible Wall/Block**: General term for a wall or a block that blocks the operators which cannot be seen.
	* **Zipline Permeable Invisible Wall**: An **invisible wall** that can be crossed with a zipline but blocks the operators. *(i.e. walls from Sword Vault Dale)* *[this name is long, ideally use "Zippable" in the context of invisible walls]*
	* **Zipline Impenetrable Invisible Wall**: An **invisible wall** that blocks both operatorss and ziplines. *(i.e. walls from Kohl Plant in Originium Science Park)* *[this name is long, ideally use "Not Zippable" in the context of invisible walls]*
	* **Zipline Clippable Invisible Wall**: A **zipline impenetrable invisible wall** in which you can clip a zipline partially or fully inside. Clipped zips will show up as valid during placement but will show that it is obstructed when attempting to use it. *(this is rarely used as there are very few spots where this happens)*

- **Eviction Zone**: General term for zones that teleport you after 3 seconds. *(Starting from v1.4, all types of eviction zones are NetLimiter bypassable)*
	* **Eviction Wall**: Walls of an **eviction zone** that restrict your horizontal movement to map bounds.
	* **Eviction Ceiling/Floor**: Ceiling/Floor of an **eviction zone** that restrict your vertical movement to map bounds.

- **Death/Water Zone**: Volume of space that force-kills/drowns the operators immediately upon touching it.
	* **Interactive Water**: Volume of water (or any liquid) that can be controlled by the player. *(i.e. various pools in Wuling)*

- **Force-Teleport Zone / TP Zone**: Volume of space that immediately fades-out and teleports the operators to the last valid position upon touching it.

- **Respawn Tile**: An area or AIC tile on which it is valid for the operators to respawn. *(i.e. it gets saved as a valid position)*
	* **Non-Respawn Tile**: An area or AIC tile (or a space lacking them) where the operators is not capable of respawning. *(inverse of a **Respawn Tile**)*

- **Share Zone/Tile**: General term for an area or AIC tile on which facilities can be shared with other players.
	* **Sharable**: When a facility is sharable. *(in a share zone)*
	* **Unsharable**: When a facility is not sharable. *(not in a share zone)*
	* **Random Sharable**: When a facility cannot be manually shared and requires a random share to take place *("a ring to pop")* before being sharable manually. *(i.e. the North-East OOB Power Plateau zipline before it was patched)*
	* **Inverse Share Zone (Theory)**: A zone that does the opposite of a share zone. *(There is suspicion that Wuling City have a large one at a certain height range as on top of the Great Wall, there are areas where facilities aren't sharable but the areas above or below them are)*

- **Fake Terrain/[Object]**: A piece of terrain and/or some [object] that is visible but doesn't have any collision, leading to operators falling straight through them. *(Despite their lack of collision, some of them allows having facilities placed on them, letting players parkour on facilities)*

- **Invisible Terrain/[Object]**: A piece of terrain and/or some [object] that has AIC tiles on it but isn't visually there. This is common with models that were moved during updates without refreshing the AIC tiles or background mountains that disappear as you switch regions. *(i.e. the North Wuling-City mountains when you are in Yinglung Pass)*

# Techniques

- **Jump Place**: A trick where placement of a facility requires the player to jump and quickly place.
- **Alt Place**: A trick where placement of a facility requires the player to hold ALT when placing for the increased placement radius.
- **Camera Cancel**: Using the Photo-Mode's Camera Control function to cancel the operators's current animation.
- **Teleport Trick**: *[Used in the context of cable routing in Valley 4]* A trick where you either use Teleport Points *or* utilize the **Fall Timer** mechanic to route straight cables between two relays or pylons.

- **[Facility] Jump**: A subset of techniques using facilities to help reach higher places.
	* **Thermal Jump/Boost**: A technique where you squeeze a character between Thermal Banks while jumping to get a jump boost onto a high ledge.
	* **Crucible Jump**: A technique where you clip yourself into a Reactor Crucible, then do Jump > Attack > Camera Cancel to temporarily slide on top of it, giving you a chance to **Alt Place** a facility on a high surface.
	* **Pipe Jump**: A method similar to Crucible Jump but with Pipe Logistics Facilities.
	* **Stash Jump**: A method where you can get an operator stuck inside an Easy Stash and jump to get halfway stuck on the roof of it. *(Fixed in 1.3 after they made them bigger)*
	* **[No term for this]**: Using the platforms of facilities to perform slightly higher jumps to ledges that are just a tiny bit too high.
	* **[Facility] Slide (?)**: A technique where the operators falls and slide onto the side of a facility *(Thermal Bank, Relay, and/or Memo Beacon)* to get slightly launched in a direction.

- **Parkour(able) / Climb(able) / "Goatable"**: Being able to use regular jumping mechanics of the game to reach a certain spot.
	* **Wiggle**: A technique where the operators rubs against a wall for a *very... very long time* to ascend a corner of some mountain.
	* **Wall Slide**: A technique where the operators jumps then slides on an invisible wall to reach a desired destination.

- [PATCHED] **Helicopter**: A technique where you use Yvonne and Laevatain (or just one of them) to vertically ascend into the air. *(patched since v1.1 but there is still a version that is slower and more inconsistent)*
	* **[No term for this]**: A sub-technique where you use an Ult animation object to temporarily stand on and jump to achieve horizontal movement. *(Also patched since v1.1 and no replacement found so far)*

- [PATCHED] **Airplane**: A technique where you enter a half-drowned state resulting in no gravity or collision, allowing you to effecively "noclip." *(patched since v1.3 although there is implication that the core bug still exist)*
	* **Death Loop**: A preliminary part of triggering airplane where you respawn underwater and immediately enter the pre-drowning status before eventually drowning and repeating the cycle.
	* **Tilt(ing)**: A process in airplane where you repeatidly move in a circular motion to slowly tilt your operator, allowing vertical movement.

# Special

- **Netlimiter**: A program used to throttle your internet speed, letting you enter eviction areas for up to 10 seconds before the game times you out.

- **Pergola**: The outdoor seating areas you see around in Wuling. I'm not sure about other servers but we in NA/EU & ASIA try to put zips on all of them whenever they're feasible and placeable. *(Sometimes, this is interchangeably used for the huts on top of the Wuling wall, so read the context!)*

- **"Landscape"**: A technical term referring to the heightmap based terrain that is used in some parts of the map. Sometimes, this terrain exist below mesh based terrain. A clear indicator of a Landscape is if you go out of bounds and the floor goes in weird spikey patterns or very smooth rolling hills vibe. *(Zips can let you go through pieces of Landscapes)*

- **"Mesh Terrain"**: A technical term referring to 3D models are used to form a piece of terrain, such as cliffs, overhangs, and caves, as they are not possible with the heightmap based landscape system. *(Note: In cases where Mesh Terrain is used, the Landscape plane is either blended in, shifted down, or completely removed. If you see double layered landscape, it was probably shifted down instead of removed... Also note that Landscape systems can only deform a 2D plane up and down, if a piece of land does more than that, it is likely Mesh-based Terrain)*
