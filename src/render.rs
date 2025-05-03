// SPDX-FileCopyrightText: 2010-2025 Friedrich von Never <friedrich@fornever.me>
//
// SPDX-License-Identifier: MIT

fn draw_screen() {
    update_texture();
    render_texture();
}

fn update_texture() {
    map.draw();
    render_info();
}

fn render_texture() {
    SDL_UpdateTexture(texture, nullptr, pixels.data(), screenWidth * sizeof(Uint32));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}
