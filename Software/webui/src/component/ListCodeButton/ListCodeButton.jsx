import React from "react";
import "./ListCodeButton.css";
import { useActionState } from "react";

function ListCodeButton() {
  const data = [
    { id: 1, label: "Ctrl", action: "{CTRL}" },
    { id: 2, label: "Shift", action: "{SHIFT}" },
    { id: 3, label: "Alt", action: "{ALT}" },
    { id: 4, label: "Windows", action: "{WINDOWS}" },
    { id: 5, label: "Up Arrow", action: "{UP_ARROW}" },
    {id:6,label:"Down Arrow",action: "{DOWN_ARROW}"},
    {id:7,label:"Up Arrow",action: "{UP_ARROW}"},
    {id:8,label:"Left Arrow",action:"{LEFT_ARROW}"},
    {id:9,label:"Right Arrow",action:"{RIGHT_ARROW}"},
    {id:10, label:"Back Space",action:"{BACKSPACE}"},
    {id:11, label:"Tab",action:"{TAB}"},
    {id:12,label:"Return",action:"{RETURN}"},
    {id:13,label:"Esc",action:"{ESC}"},
    {id:14,label:"Insert",action:"{INSERT}"},
    {id:15,label:"Print screen",action:"{PRTSC}"},
    {id:16,label:"Delete",action:"{DELETE}"},
    {id:17,label:"Page Up",action:"{PGUP}"},
    {id:18,label:"Page Down",action:"{PGDN}"},
    {id:19,label:"Home",action:"{HOME}"},
    {id:20,label:"End",action:"{END}"},
    {id:21,label:"Caps Lock",action:"{CPLK}"},
    {id:22,label:"F1",action:"{F1}"},
    {id:23,label:"F2",action:"{F2}"},
    {id:24,label:"F3",action:"{F3}"},
    {id:25,label:"F4",action:"{F4}"},
    {id:26,label:"F5",action:"{F5}"},
    {id:27,label:"F6",action:"{F6}"},
    {id:28,label:"F7",action:"{F7}"},
    {id:29,label:"F8",action:"{F8}"},
    {id:30,label:"F9",action:"{F9}"},
    {id:31,label:"F10",action:"{F10}"},
    {id:32,label:"F11",action:"{F11}"},
    {id:33,label:"F12",action:"{F12}"},
    {id:34,label:"Enter",action:"{ENTER}"}
  ];

  return (
    <div className="table-container">
      <h2 className="table-title">Bảng mã</h2>
      <table className="styled-table">
        <thead>
          <tr>
            <th>Nút bấm</th>
            <th>Code</th>
          </tr>
        </thead>
        <tbody>
          {data.map((row, index) => (
            <tr key={row.id} className={index % 2 === 0 ? "even" : "odd"}>
              <td>{row.label}</td>
              <td>{row.action}</td>
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
}

export default ListCodeButton;
