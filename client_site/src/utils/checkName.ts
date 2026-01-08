import { Filter as BadWordsFilter } from 'bad-words';
// @ts-ignore
import leoProfanity from 'leo-profanity';

// Initialize dictionaries
const badWordsFilter = new BadWordsFilter();
leoProfanity.loadDictionary('en');

// Narrow the type safely using a type assertion
const leoWords = (leoProfanity as unknown as { getDictionary: () => string[] }).getDictionary();

const allBannedWords = new Set([
    ...badWordsFilter.list.map((w) => w.toLowerCase()),
    ...leoWords.map((w) => w.toLowerCase()),
]);

/**
 * Normalize nickname: strip non-alphanumerics and lowercase everything
 */
function normalize(nickname: string): string {
    return nickname.replace(/[^a-z0-9]/gi, '').toLowerCase();
}

/**
 * Check if the normalized name contains any banned word as a substring
 */
export function badName(nickname: string): boolean {
    const cleaned = normalize(nickname);

    for (const word of allBannedWords) {
        if (cleaned.includes(word)) {
            return true;
        }
    }

    return false;
}