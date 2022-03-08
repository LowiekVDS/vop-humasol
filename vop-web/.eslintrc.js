module.exports = {
    "env": {
        "browser": true,
        "es2021": true
    },
    "extends": [
        "eslint:recommended",
        "plugin:react/recommended",
        "plugin:@typescript-eslint/recommended"
    ],
    "parser": "@typescript-eslint/parser",
    "parserOptions": {
        "ecmaFeatures": {
            "jsx": true
        },
        "ecmaVersion": "latest",
        "sourceType": "module"
    },
    "plugins": [
        "formatjs",
        "react",
        "@typescript-eslint"
    ],
    "rules": {
        "react/react-in-jsx-scope": 0,
        "@typescript-eslint/no-var-requires": 0,
        "no-constant-condition": 0,
        "formatjs/enforce-id": 2
    }
}
