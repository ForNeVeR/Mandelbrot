/*
 * SPDX-FileCopyrightText: 2010-2025 Friedrich von Never <friedrich@fornever.me>
 *
 * SPDX-License-Identifier: MIT
 */

// This file used for storing font definition.
type PixelArray = [[bool; 8]; 8];

const SPACE: PixelArray = [
    [false, false, false, false, false, false, false, false],
    [false, false, false, false, false, false, false, false],
    [false, false, false, false, false, false, false, false],
    [false, false, false, false, false, false, false, false],
    [false, false, false, false, false, false, false, false],
    [false, false, false, false, false, false, false, false],
    [false, false, false, false, false, false, false, false],
    [false, false, false, false, false, false, false, false]
];

const DOT: PixelArray = [
    [false, false, false, false, false, false, false, false],
    [false, false, false, false, false, false, false, false],
    [false, false, false, false, false, false, false, false],
    [false, false, false, false, false, false, false, false],
    [false, false, false, false, false, false, false, false],
    [false, false, false, false, false, false, false, false],
    [false, false, false, true, true, false, false, false],
    [false, false, false, true, true, false, false, false]
];

const COLON: PixelArray = [
    [false, false, false, false, false, false, false, false],
    [false, false, false, true, true, false, false, false],
    [false, false, false, true, true, false, false, false],
    [false, false, false, false, false, false, false, false],
    [false, false, false, false, false, false, false, false],
    [false, false, false, false, false, false, false, false],
    [false, false, false, true, true, false, false, false],
    [false, false, false, true, true, false, false, false]
];

const MINUS: PixelArray = [
    [false, false, false, false, false, false, false, false],
    [false, false, false, false, false, false, false, false],
    [false, false, false, false, false, false, false, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, true, true, true, true, false],
    [false, false, false, false, false, false, false, false],
    [false, false, false, false, false, false, false, false],
    [false, false, false, false, false, false, false, false]
];

const PLUS: PixelArray = [
    [false, false, false, false, false, false, false, false],
    [false, false, false, true, true, false, false, false],
    [false, false, false, true, true, false, false, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, true, true, true, true, false],
    [false, false, false, true, true, false, false, false],
    [false, false, false, true, true, false, false, false],
    [false, false, false, false, false, false, false, false]
];

const ZERO: PixelArray = [
    [false, false, false, false, false, false, false, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, false, false, true, true, false],
    [false, true, true, false, false, true, true, false],
    [false, true, true, false, false, true, true, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, true, true, true, true, false]
];

const ONE: PixelArray = [
    [false, false, false, false, false, false, false, false],
    [false, false, false, true, true, false, false, false],
    [false, false, true, true, true, false, false, false],
    [false, false, true, true, true, false, false, false],
    [false, false, false, true, true, false, false, false],
    [false, false, false, true, true, false, false, false],
    [false, false, false, true, true, false, false, false],
    [false, false, false, true, true, false, false, false]
];

const TWO: PixelArray = [
    [false, false, false, false, false, false, false, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, false, false, true, true, false],
    [false, false, false, false, true, true, true, false],
    [false, false, true, true, true, true, false, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, true, true, true, true, false]
];

const THREE: PixelArray = [
    [false, false, false, false, false, false, false, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, false, false, true, true, false],
    [false, false, false, false, true, true, true, false],
    [false, true, true, false, false, true, true, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, true, true, true, true, false]
];

const FOUR: PixelArray = [
    [false, false, false, false, false, false, false, false],
    [false, true, true, false, false, true, true, false],
    [false, true, true, false, false, true, true, false],
    [false, true, true, false, false, true, true, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, true, true, true, true, false],
    [false, false, false, false, false, true, true, false],
    [false, false, false, false, false, true, true, false]
];

const FIVE: PixelArray = [
    [false, false, false, false, false, false, false, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, false, false, false, false, false],
    [false, true, true, true, true, true, true, false],
    [false, false, false, false, false, true, true, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, true, true, true, true, false]
];

const SIX: PixelArray = [
    [false, false, false, false, false, false, false, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, false, false, false, false, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, false, false, true, true, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, true, true, true, true, false]
];

const SEVEN: PixelArray = [
    [false, false, false, false, false, false, false, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, true, true, true, true, false],
    [false, true, false, false, false, true, true, false],
    [false, false, false, false, true, true, true, false],
    [false, false, false, false, true, true, false, false],
    [false, false, false, false, true, true, false, false],
    [false, false, false, false, true, true, false, false]
];

const EIGHT: PixelArray = [
    [false, false, false, false, false, false, false, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, false, false, true, true, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, false, false, true, true, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, true, true, true, true, false]
];

const NINE: PixelArray = [
    [false, false, false, false, false, false, false, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, false, false, true, true, false],
    [false, true, true, true, true, true, true, false],
    [false, false, false, false, false, true, true, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, true, true, true, true, false]
];

const A_CAPITAL: PixelArray = [
    [false, false, false, false, false, false, false, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, false, false, true, true, false],
    [false, true, true, false, false, true, true, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, false, false, true, true, false],
    [false, true, true, false, false, true, true, false]
];

const C_CAPITAL: PixelArray = [
    [false, false, false, false, false, false, false, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, false, false, false, false, false],
    [false, true, true, false, false, false, false, false],
    [false, true, true, false, false, false, false, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, true, true, true, true, false]
];

const E_CAPITAL: PixelArray = [
    [false, false, false, false, false, false, false, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, false, false, false, false, false],
    [false, true, true, true, true, true, false, false],
    [false, true, true, false, false, false, false, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, true, true, true, true, false]
];

const F_CAPITAL: PixelArray = [
    [false, false, false, false, false, false, false, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, false, false, false, false, false],
    [false, true, true, true, true, false, false, false],
    [false, true, true, false, false, false, false, false],
    [false, true, true, false, false, false, false, false],
    [false, true, true, false, false, false, false, false]
];

const L_CAPITAL: PixelArray = [
    [false, false, false, false, false, false, false, false],
    [false, true, true, false, false, false, false, false],
    [false, true, true, false, false, false, false, false],
    [false, true, true, false, false, false, false, false],
    [false, true, true, false, false, false, false, false],
    [false, true, true, false, false, false, false, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, true, true, true, true, false]
];

const P_CAPITAL: PixelArray = [
    [false, false, false, false, false, false, false, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, false, false, true, true, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, false, false, false, false, false],
    [false, true, true, false, false, false, false, false],
    [false, true, true, false, false, false, false, false]
];

const S_CAPITAL: PixelArray = [
    [false, false, false, false, false, false, false, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, false, false, false, false, false],
    [false, true, true, true, true, true, true, false],
    [false, false, false, false, false, true, true, false],
    [false, true, true, true, true, true, true, false],
    [false, true, true, true, true, true, true, false]
];

const UNKNOWN: PixelArray = [
    [false, false, false, false, false, false, false, false],
    [false, false, false, false, false, false, false, false],
    [false, false, false, false, false, false, false, false],
    [false, false, false, false, false, false, false, false],
    [false, false, false, false, false, false, false, false],
    [false, false, false, false, false, false, false, false],
    [false, false, false, false, false, false, false, false],
    [false, false, false, false, false, false, false, false]
];

/// This function returns array 8x8 of bool values, where true means black color of
/// pixel and false means transparent color of pixel.
pub fn get_character(character: char) -> &'static PixelArray {
    match character {
        ' ' => &SPACE,
        '.' => &DOT,
        ':' => &COLON,
        '-' => &MINUS,
        '+' => &PLUS,
        '0' => &ZERO,
        '1' => &ONE,
        '2' => &TWO,
        '3' => &THREE,
        '4' => &FOUR,
        '5' => &FIVE,
        '6' => &SIX,
        '7' => &SEVEN,
        '8' => &EIGHT,
        '9' => &NINE,
        'A' => &A_CAPITAL,
        'C' => &C_CAPITAL,
        'E' => &E_CAPITAL,
        'F' => &F_CAPITAL,
        'L' => &L_CAPITAL,
        'P' => &P_CAPITAL,
        'S' => &S_CAPITAL,
        _ => &UNKNOWN
    }
}