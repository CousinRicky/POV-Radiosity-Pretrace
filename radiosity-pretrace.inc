/* radiosity_pretrace.inc 1.1.1
 * Persistence of Vision Ray Tracer include file
 *
 * Sets up radiosity pretrace parameters using some of the recommendations in
 * the Radiosity Voodoo thread in povray.text.tutorials.
 *
 * Copyright © 2014 - 2023 Richard Callwood III.  Some rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Vers.  Date         Notes
 * -----  ----         -----
 * 1.0    2014-Jan-16  Created.
 * 1.0a   2014-Jan-17  A correction is made to the user manual.
 *        2019-Jul-08  Invalid radiosity settings are written to the debug
 *                     stream regardless of the Radiosity_Pretrace_debug
 *                     setting.
 * 1.1    2019-Jul-08  View_POV_Include_Stack is utilized.
 *        2023-Feb-19  The POV-Ray version is auto-detected within a range.
 * 1.1.1  2023-Feb-19  The license is changed.
 */
#ifndef (Radiosity_Pretrace_Inc_Temp)
#declare Radiosity_Pretrace_Inc_Temp = version;
#version max (3.5, min (3.8, version));
#declare RADIOSITY_PRETRACE_VERSION = 1.11;
#ifdef (View_POV_Include_Stack)
  #debug "#include \"radiosity-pretrace.inc\" //version 1.1.1\n"
#end

#ifndef (Radiosity_Pretrace_debug) #declare Radiosity_Pretrace_debug = no; #end

#macro Radiosity_Pretrace (Max, Min)
  #local radiosity_Min =
    (Min < 1? Min: Min / max (image_width, image_height));
  #local radiosity_Max =
    #if (Max / radiosity_Min > 0)
      radiosity_Min * pow (2, floor (ln (Max / radiosity_Min) / ln(2)));
    #else
      Max;
    #end
  #if
  ( Radiosity_Pretrace_debug |
    radiosity_Min > radiosity_Max | radiosity_Min > 1 | radiosity_Min <= 0
  )
    #debug "Radiosity_Pretrace ("
    #debug str (Max, 0, -1)
    #debug ", "
    #debug str (Min, 0, -1)
    #debug "):\n  pretrace_start "
    #debug str (radiosity_Max, 0, -1)
    #debug "\n  pretrace_end "
    #debug str (radiosity_Min, 0, -1)
    #debug "\n"
  #end
  pretrace_start radiosity_Max
  pretrace_end radiosity_Min
#end

#version Radiosity_Pretrace_Inc_Temp;
#end
