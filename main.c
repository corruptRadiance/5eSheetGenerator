#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "data.c"

int RollSkillCheck(struct s_sheet *, struct s_skill);
void DisplaySheetValues(struct s_sheet *);
void PromptCharacterInfo(struct s_sheet *);

int main(){
    srand(time(NULL));
    struct s_sheet *p_sheet = NewSheet();

    RollAllStats(p_sheet, 4);
    UpdateAllSkills(p_sheet);
    PromptCharacterInfo(p_sheet);

    DisplaySheetValues(p_sheet);

    printf("\nPress ENTER to exit.");
    getchar();
    
    free(p_sheet);
    return 0;
}

int RollSkillCheck(struct s_sheet *sheet, struct s_skill skill){
    int result = (rand() % 20) + skill.bonus + 1;

    if (skill.proficient){
        result += sheet->proficiency;
    }

    return result;
}

void DisplaySheetValues(struct s_sheet *sheet){
    // Print Character Info
    printf("== Character Info ==\n");
    printf("%s, %s\n", sheet->characterName, sheet->pronouns);
    printf("Played by: %s\n\n", sheet->playerName);
    printf("%s\n", sheet->personality);

    // Print Stats
    printf("\n== Stats ==\n");
    printf("Character Level: %i\n", sheet->level);
    printf("| Strength     | Level: %i | Bonus: %i |\n", sheet->strength.level, sheet->strength.bonus);
    printf("| Dexterity    | Level: %i | Bonus: %i |\n", sheet->dexterity.level, sheet->dexterity.bonus);
    printf("| Constitution | Level: %i | Bonus: %i |\n", sheet->constitution.level, sheet->constitution.bonus);
    printf("| Intelligence | Level: %i | Bonus: %i |\n", sheet->intelligence.level, sheet->intelligence.bonus);
    printf("| Wisdom       | Level: %i | Bonus: %i |\n", sheet->wisdom.level, sheet->wisdom.bonus);
    printf("| Charisma     | Level: %i | Bonus: %i |\n", sheet->charisma.level, sheet->charisma.bonus);
}

void PromptCharacterInfo(struct s_sheet *sheet){
    // Store Player Name
    printf("What is your player's name?\n>");
    fgets(sheet->playerName, sizeof(sheet->playerName), stdin);
    sheet->playerName[strcspn(sheet->playerName, "\n")] = 0;
    
    // Store Character Name
    printf("What is your character's name?\n>");
    fgets(sheet->characterName, sizeof(sheet->characterName), stdin);
    sheet->characterName[strcspn(sheet->characterName, "\n")] = 0;
    
    // Store Pronouns
    printf("What are your character's pronouns?\n>");
    fgets(sheet->pronouns, sizeof(sheet->pronouns), stdin);
    sheet->pronouns[strcspn(sheet->pronouns, "\n")] = 0;
    
    // Store Personality
    printf("Give a brief summary of your character's personality [256 character limit]\n>");
    fgets(sheet->personality, sizeof(sheet->personality), stdin);
    sheet->personality[strcspn(sheet->personality, "\n")] = 0;
}