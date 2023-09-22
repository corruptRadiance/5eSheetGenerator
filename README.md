## GOALS:
- [x] Create structs for stats/bonuses
- [x] Create a struct to represent a sheet
- [x] Create function to return a randomly rolled stat
- [x] Fix incorrect stat bonus with negative stat levels
- [x] Store stats as named members of sheet
- [ ] ~~Store skills as named members of stats~~
- [x] Create function to populate skill bonuses
- [x] Create function to roll all stats
- [x] Create function to roll skill check
- [x] Test SetSkillProficiency() w/ roll function
- [x] Create function to initialize a basic sheet
- [x] Fix UpdateAllSkills() check (can't check for NULL?)
- [x] Make UpdateAllSkills() not set every skill prociency to false
- [x] Create function to display sheet values
- [x] Create function to prompt the player for character info
- [x] Organize project into separate files

- [ ] Fix PromptCharacterInfo() overflowing from the i/o stream
- [ ] Create function to check for invalid stats
- [ ] Add invalid stat check function to every function that relies on a stat to return

- [ ] Store each sheet as a file on the computer

## OPTIMIZATION:
- [ ] Split RollForStat() steps into smaller functions
- [ ] Create meta structure for storing skills under one parent stat (?)
- [ ] Find a way to get variable names to iterate stat names
  
## NOTES:

### Systems to recreate:
- [x] Character Info (including motivations)
- [x] Stats with Manual Rolls (Roll 3 or 4d6, drop the lowest)
- [ ] Skills w/ proficiency
- [ ] Saving throws w/ proficiency
- [ ] Hit Points/Dice

Don't entirely recreate the sheet from the ground up,
focus on broad systems like stats and character motivations
(that are coincidentally easier to implement hehe)

Learn "proper" format to store files