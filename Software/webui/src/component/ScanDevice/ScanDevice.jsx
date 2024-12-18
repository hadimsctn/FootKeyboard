import React from "react";
import './ScanDevice.css'

const ScanDevice = () => {
    const data = [
        "Dòng 1",
        "Dòng 2",
        "Dòng 3",
        "Dòng 4",
        "Dòng 5"
      ];
    
      return (
        <div className="ScanDevice">
          <table className="ScanDevice-table">
            <thead>
              <tr>
                <th>Scan Device</th>
              </tr>
            </thead>
            <tbody>
              {data.map((item, index) => (
                <tr key={index}>
                  <td>{item}</td>
                </tr>
              ))}
            </tbody>
          </table>
        </div>
      );
}

export default ScanDevice