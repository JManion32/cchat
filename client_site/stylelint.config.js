/** @type {import("stylelint").Config} */
export default {
    extends: ['stylelint-config-standard'],
    ignoreFiles: ['dist/**', 'node_modules/**', 'public/**', 'src/assets/**'],
    rules: {
        'declaration-no-important': true,

        'color-function-notation': null,
        'alpha-value-notation': null,
        'color-function-alias-notation': null,
        'import-notation': null,
        'media-feature-range-notation': null,
        'keyframes-name-pattern': null,
        'at-rule-no-unknown': null,
        'no-duplicate-selectors': null,
        'color-hex-length': null,
    },
};
