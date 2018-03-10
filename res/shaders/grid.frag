#version 400 core

in vec2 t_uv;
in vec3 t_color;

out vec4 o_fragment;

uniform mat4 u_view;
uniform mat4 u_model;

float extract_scale( mat4 model ) {
    return length(vec3(length(model[0]),
                       length(model[1]),
                       length(model[2])));
}

void main() {

    // Scale grid to camera
    float scale = extract_scale( u_model );
    float camera_z = -u_view[3].z;
    float thickness = 0.01 * camera_z / scale;

    float divisions = 10.0;
    float delta = 0.05 / 2.0;

    float x = fract(t_uv.x * divisions);
    x = min(x, 1.0 - x);

    float xdelta = fwidth(x);
    x = smoothstep(x - xdelta, x + xdelta, thickness);

    float y = fract(t_uv.y * divisions);
    y = min(y, 1.0 - y);

    float ydelta = fwidth(y);
    y = smoothstep(y - ydelta, y + ydelta, thickness);

    float colour = clamp(x + y, 0.0, 1.0);
    float alpha = ceil(colour - 0.5);
    o_fragment = vec4(colour, colour, colour, alpha);
}