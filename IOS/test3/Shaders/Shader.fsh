//
//  Shader.fsh
//  test3
//
//  Created by Jackie Gleason on 5/29/13.
//  Copyright (c) 2013 Jackie Gleason. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
